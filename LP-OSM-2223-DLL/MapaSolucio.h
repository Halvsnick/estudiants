#pragma once
#include "MapaBase.h"
#include "XML4OSMUtil.h"
#include "PuntDeInteresBase.h"
#include "Common.h"
#include <string>
#include "pch.h"
#include <vector>
#include "PuntInteresBotiga.h"
#include "PuntInteresRestaurant.h"
#include "CamiSolució.h"
#include "CamiBase.h"
#include <iostream>
#include <unordered_map>


using namespace std;

class MapaSolucio : public MapaBase {
private:

	std::vector<PuntDeInteresBase*> m_pdisList;
	std::vector<CamiBase*> m_wayList;
	std::vector<XmlElement> VectorNodes;				//vector on guardar els nodes
	//unordered_map<Coordinate, XmlElement> VectoresWoPI;		//tabla de hash per elimiar els repes
	std::unordered_map<std::pair<double, double>, bool, MyHash> HashWoPI;

public:

	void getPdis(std::vector<PuntDeInteresBase*>& pdis); 

	void getCamins(std::vector<CamiBase*>& camins)
	{
		CamiSolucio* c = new CamiSolucio();
	}
	void parsejaXmlElements(std::vector<XmlElement>& xmlElements)
	{
		double lat;
		double lon;

		for (XmlElement& WoPI : xmlElements)				 //WoPI = Ways o Punts de Interes
		{
			if (WoPI.id_element == "node")
			{
				int i = 0; 
				bool T_lat = false;
				bool T_lon = false;
				bool T_Time = false;
				while (i < WoPI.atributs.size() && ((!T_lon) || (!T_lat) || (!T_Time)))
				{
					if (WoPI.atributs[i].first == "lat")
					{
						lat = std::stod(WoPI.atributs[i].second);
						T_lat = true;
					}
					if (WoPI.atributs[i].first == "lon")
					{
						lon = std::stod(WoPI.atributs[i].second);
						T_lon = true;
					}
					if (WoPI.atributs[i].first == "timestamp")
					{
						//bucle for per dins dels diferents timestamp i agafar el mes recent 
					}
					i++;
				}
				if (HashWoPI.find({ lat, lon }) == HashWoPI.end())   //WoPI no agregado => lo agrego 
				{
					// Marcar esta coordenada como vista
					HashWoPI[{lat, lon}] = true;
				}
				else
				{
					for (auto it = VectorNodes.begin(); it != VectorNodes.end();)
					{
						const XmlElement& WoPI = *it;

						if (HashWoPI.find({ lat, lon }) != HashWoPI.end())
							it = VectorNodes.erase(it); // WoPI ya existe en VectoresWoPI, entonces lo eliminamos de VectorNodes
						else
							++it;
							// WoPI no existe en VectoresWoPI, continuamos con el siguiente elemento
					}
				}
				// Agregar el elemento a VectorNodes
				VectorNodes.push_back(WoPI);
			}

		}

	}
};

void MapaSolucio::getPdis(std::vector<PuntDeInteresBase*>& pdis)
{
	//convertir el VectorNodes clase XmlElements a PuntdeInteresBase
	double lat;
	double lon;

	std::string shopTag = "";
	std::string cuisine = "";
	std::string name = "";

	bool botiga = false;
	bool restaurant = false;
	bool wheelchair = false;

	//Punts de interes
	for (XmlElement& xmlElement : VectorNodes)
	{
		if (xmlElement.id_element == "node")						//Check that it is of type node
		{
			//Iterate through attributes
			for (int i = 0; i < xmlElement.atributs.size(); i++)
			{
				if (xmlElement.atributs[i].first == "lat")			//Latitud
					lat = std::stod(xmlElement.atributs[i].second);
				if (xmlElement.atributs[i].first == "lon")			//Longitude
					lon = std::stod(xmlElement.atributs[i].second);
			}

			//Iterate through childs
			for (int i = 0; i < xmlElement.fills.size(); i++)
			{
				if (xmlElement.fills[i].first == "tag")
				{
					std::pair<std::string, std::string> valorTag = Util::kvDeTag(xmlElement.fills[i].second);
					if (valorTag.first == "shop")					//Shop tag
					{
						botiga = true;
						shopTag = valorTag.second;
					}
					if (valorTag.first == "amenity")				//Amenity
					{
						if (valorTag.second == "restaurant")		//Check that it is of type restaurant
							restaurant = true;
					}
					if (valorTag.first == "name")					//Name
						name = valorTag.second;
					if (valorTag.first == "wheelchair")				//Wheelchair
						wheelchair = (valorTag.second == "yes") ? true : false;
					if (valorTag.first == "cuisine")				//Cuisine
						cuisine = valorTag.second;
				}

			}
		}

		if (botiga)
		{
			PuntInteresBotiga* b = new PuntInteresBotiga({ lat, lon }, name, shopTag, wheelchair);
			m_pdisList.push_back(b);
		}
		else if (restaurant)
		{
			PuntInteresRestaurant* r = new PuntInteresRestaurant({ lat, lon }, name, cuisine, wheelchair);
			m_pdisList.push_back(r);
		}
	}
}





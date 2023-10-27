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
		// Iterar a traves dels elements xmlElements
		for (XmlElement& xml : xmlElements)
		{
			// Comprovar si l'element es de tipus "node"
			if (xml.id_element == "node")
			{
				double lat = 0;
				double lon = 0;

				std::string name = "";
				std::string cuisine = "";
				std::string shopTag;

				bool wheelchair = false;

				// Iterar a traves dels atributs de l'element "node"
				for (int i = 0; i < xml.atributs.size(); i++)
				{
					if (xml.atributs[i].first == "lat")
						lat = std::stod(xml.atributs[i].second);
					if (xml.atributs[i].first == "lon")
						lon = std::stod(xml.atributs[i].second);
				}

				// Flags per detectar si s'han trobat atributs especifics
				bool restaurant = false;		// Indica si es un restaurant
				bool shop = false;				// Indica si es una botiga
				bool highway = false;
				bool publicTransport = false;
				bool access = false;
				bool entrance = false;

				// Iterar a traves dels elements secundaris (childs)
				for (int i = 0; i < xml.fills.size(); i++)
				{
					if (xml.fills[i].first == "tag")
					{
						// Obtenir el par clau-valor de l'element tag
						std::pair<std::string, std::string> valorTag = Util::kvDeTag(xml.fills[i].second);

						// Comprovar si s'han trobat atributs rellevants
						if (valorTag.first == "highway")
						{
							highway = true;
						}
						if (valorTag.first == "public_transport")
						{
							publicTransport = true;
						}
						if (valorTag.first == "entrance")
						{
							entrance = true;
						}
						if (valorTag.first == "access")
						{
							access = true;
						}
						if (valorTag.first == "name")
						{
							name = valorTag.second;
						}
						if (valorTag.first == "cuisine")
						{
							cuisine = valorTag.second;
						}
						if (valorTag.first == "wheelchair")
						{
							// Comprobar si el restaurant es accessible en cadira de rodes
							wheelchair = (valorTag.second == "yes") ? true : false;
						}
						if (valorTag.first == "amenity")
						{
							if (valorTag.second == "restaurant")
								restaurant = true;
						}
						if (valorTag.first == "shop")
						{
							shopTag = valorTag.second;
							shop = true;
						}
					}
				}

				if (!highway && !publicTransport && !entrance && !access)
				{
					// Verificar si s'han trobat tots els atributs necessaris per ser considerat un restaurant
					if (restaurant && !name.empty())
					{
						// Afegir a la lista de restaurants
						m_pdisList.push_back(new PuntInteresRestaurant({ lat, lon }, name, cuisine, wheelchair));
					}
					// Verificar si s'han trobat tots els atributs necessaris per ser considerat una botiga
					if (shop && !name.empty())
					{
						// Afegir a la lista de botigues
						m_pdisList.push_back(new PuntInteresBotiga({ lat, lon }, name, shopTag, wheelchair));
					}
					// Verificar si s'han trobat tots els atributs necessaris per ser considerat un punt d'interes
					if (!shop && !restaurant && !name.empty())
					{
						// Afegir a la lista de punts d'interes
						m_pdisList.push_back(new PuntDeInteresBase({ lat, lon }, name));
					}
				}
			}
		}
	}
	/*
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

	}*/
};


void MapaSolucio::getPdis(std::vector<PuntDeInteresBase*>& pdis)
{
	//convertir el VectorNodes clase XmlElements a PuntdeInteresBase
	/*double lat;
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
	}*/
	pdis = m_pdisList;

}








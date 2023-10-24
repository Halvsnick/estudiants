#pragma once
#include "MapaBase.h"
#include "XML4OSMUtil.h"
#include "PuntDeInteresBase.h"
#include "Common.h"
#include <string>
#include "pch.h"
#include <vector>
#include "PuntInteresBotiga.h"
#pragma once
#include "PuntInteresRestaurant.h"
#include "CamiSolució.h"
#include "CamiBase.h"
#include <vector>
#include <string>

using namespace std;

class MapaSolucio : public MapaBase {
private:
	/////INICIO ESTRUCTURA DE GUARDAR XML/////////////
	vector<PuntDeInteresBase*> m_puntsInteres;
	vector<CamiBase*> m_camins;
	/////////////////////////////////////
	PuntInteresBotiga shop;
	PuntInteresRestaurant restaurant;
	Coordinate coord;

public:

	void getPdis(std::vector<PuntDeInteresBase*>& pdis)
	{
		// crear LA BOTIGA 
		string shopTag = "bakery";
		std::string name = "La Millor Pastisseria";
		bool wheelchair = true;

		Coordinate coord;
		coord.lat = 41.4918606;
		coord.lon = 2.1465411;

		PuntDeInteresBase* newShop = new PuntInteresBotiga(coord, name, shopTag, wheelchair);

		pdis.push_back(newShop);

		// crear EL RESTAURANT 

		string TypeCuisine = "regional";
		name = "El Millor Restaurant";
		wheelchair = true;

		coord.lat = 41.4902204;
		coord.lon = 2.1406477;

		PuntInteresRestaurant* newRest = new PuntInteresRestaurant(coord, name, TypeCuisine, wheelchair);
		pdis.push_back(newRest);
	}

	void getCamins(std::vector<CamiBase*>& camins) 
	{
		CamiSolucio* c = new CamiSolucio();

		camins.push_back(c);
	}

	//Falta buscar los caminos
	void parsejaXmlElements(std::vector<XmlElement>& xmlElements) {
		double lat;
		double lon;
		string cuisine;
		string shop;
		string name;
		bool resBot; //Restaurant = true, Botiga = false
		bool wheelchair;
		for (std::vector<XmlElement>::iterator it = xmlElements.begin(); it != xmlElements.end(); it++)
		{

			if ((*it).id_element == "node")
			{
				//Recorrido de los atributos, buscando coordenadas
				for (int i = 0; i < (*it).atributs.size(); i++)
				{
					if ((*it).atributs[i].first == "lat")
					{
						lat = stod((*it).atributs[i].second);
					}
					if ((*it).atributs[i].first == "lon")
					{
						lon = stod((*it).atributs[i].second);
					}
				}
				//Recorrido de los hijos, buscando
				for (int i = 0; i  < (*it).fills.size(); i++)
				{
					pair<string, string> valorTag = Util::kvDeTag((*it).fills[i].second);
					if (valorTag.first == "amenity")
					{
						//Comprovando que sea restaurante
						if (valorTag.second == "restaurant")
						{
							resBot = true;
							
						}
						

					}
					//Comprovando que sea tienda y guardando el tipo
					if (valorTag.first == "shop")
					{
						resBot = false;
						shop = valorTag.second;
					}
					//Si Es restaurante, se cumplira. Buscamos los atributos de restaurante y los guardamos en variables
					if(resBot)
					{
						if (valorTag.first == "cuisine")
						{
							cuisine = valorTag.second;
						}
						if (valorTag.first == "name")
						{
							name = valorTag.second;
						}
						if (valorTag.first == "wheelchair")
						{
							wheelchair = (valorTag.second == "yes") ? true : false;
						}
					}
					if (!resBot)
					{
						
						if (valorTag.first == "name")
						{
							name = valorTag.second;
						}
						if (valorTag.first == "wheelchair")
						{
							wheelchair = (valorTag.second == "yes") ? true : false;
						}
					}
				}
			}
		}
		Coordinate c;
		c.lon = lon;
		c.lat = lat;
		if (resBot)
		{
			//Crear el punto de inters- restaurante y añadirlo al vector
			PuntDeInteresBase* p = new PuntInteresRestaurant(c,name,cuisine,wheelchair);
			m_puntsInteres.push_back(p);
		}
		else
		{
			//Crear el punto de interes - tienda y añadirlo al vector
			PuntDeInteresBase* p = new PuntInteresBotiga(c, name, shop, wheelchair);
			m_puntsInteres.push_back(p);
		}
	}
};

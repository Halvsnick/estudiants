#pragma once
#include "PuntInteresBotiga.h"
#include "PuntInteresRestaurant.h"
#include "CamiSolució.h"
#include "Util.h"

using namespace std;

class MapaSolucio : public MapaBase {													//MapaSolucio derivada de MapaBase
private:

	vector<PuntDeInteresBase*> m_WoPI;
	vector<CamiBase*> m_Ways;
	vector<string> m_Punts_id;

public:

	void getPdis(vector<PuntDeInteresBase*>& PuntsInteres)
	{ 
		PuntsInteres.clear();  //neteja el vector
		
		for (auto it = m_WoPI.begin(); it < m_WoPI.end(); it++)
		{
			if (!(*it)->getName().empty() && (*it)->getName() != "isatrap"
				&& (*it)->getName() != "itsatrap")
			//si cumpleix totes les condicions anteriors l'afegim
				PuntsInteres.push_back((*it)); 
		}
	};				

	void getCamins(std::vector<CamiBase*>& Ways)
	{
		//contingut de m_ways a ways
		Ways = m_Ways; 
	}
	void parsejaXmlElements(std::vector<XmlElement>& xmlElements)
	{
		//netejar perque caronte acepti
		m_WoPI.clear();
		m_Ways.clear();
		m_Punts_id.clear();

		// Iterar a traves dels elements xmlElements
		for (XmlElement& WoPI : xmlElements)  //WoPI = Way o Punt de Interes
		{
			// Comprovar si l'element es de tipus "node"
			if (WoPI.id_element == "node")
			{
				double lat = 0;
				double lon = 0;

				string id = "";

				// Iterar a traves dels atributs de l'element "node"
				for (int i = 0; i < WoPI.atributs.size(); i++)
				{
					if (WoPI.atributs[i].first == "id")
						id = WoPI.atributs[i].second;
					if (WoPI.atributs[i].first == "lat")
						lat = stod(WoPI.atributs[i].second);
					if (WoPI.atributs[i].first == "lon")
						lon = stod(WoPI.atributs[i].second);
				}

				
				bool restaurant = false;		// Indica si es un restaurant
				bool shop = false;				// Indica si es una botiga
				bool wheelchair = false;
				string name;
				string shopTag;
				string typeCuisine;
				string openHour;

				// Iterar a traves dels elements secundaris (childs)
				for (int i = 0; i < WoPI.fills.size(); i++)
				{
					if (WoPI.fills[i].first == "tag")
					{
						// Obtenir el par clau-valor de l'element tag
						pair<string, string> valorTag = Util::kvDeTag(WoPI.fills[i].second);

						if (valorTag.first == "name")
							name = valorTag.second;

						if (valorTag.first == "cuisine")
							typeCuisine = valorTag.second;
						
						if (valorTag.first == "wheelchair")
							// Comprobar si el restaurant es accessible en cadira de rodes
							wheelchair = (valorTag.second == "yes") ? true : false;
						
						if (valorTag.first == "amenity" && valorTag.second == "restaurant")
							restaurant = true;
						
						if (valorTag.first == "shop")
						{
							shopTag = valorTag.second;
							shop = true;
						}
					}
				}
				//guardar id del node
				m_Punts_id.push_back(id);

				if (restaurant)
					// Afegir a la lista de restaurants
					m_WoPI.push_back(new PuntInteresRestaurant({ lat, lon }, name, typeCuisine, wheelchair));
				
				if(shop)
					// Afegir a la lista de botigues
					m_WoPI.push_back(new PuntInteresBotiga({ lat, lon }, name, shopTag, wheelchair));

				if (!restaurant && !shop)
					m_WoPI.push_back(new PuntDeInteresBase({ lat, lon }, name));
			
			
			}else
				if (WoPI.id_element == "way")
				{
					vector<PuntDeInteresBase*> Nodes_relacionats;
					for (int i = 0; i < WoPI.fills.size(); i++)
					{
						if (WoPI.fills[i].first == "nd")
						{
							for (int j = 0; j < m_Punts_id.size(); j++)
							{
								if (m_Punts_id[j] == WoPI.fills[i].second[0].second)
								{
									// Afegim el node relacionat al vector nd
									Nodes_relacionats.push_back(m_WoPI[j]);
									break; 
								}
							}
						}else
							if (WoPI.fills[i].first == "tag")
							{
								vector<Coordinate> Coords;
								pair<string,string> valorTag = Util::kvDeTag(WoPI.fills[i].second);
								
								if (valorTag.first == "highway")
								{
									//recorem els nodes relacionats
									for (auto aux = Nodes_relacionats.begin(); aux != Nodes_relacionats.end(); aux++)
										Coords.push_back((*aux)->getCoord());

									CamiSolucio* way = new CamiSolucio(Coords);

									m_Ways.push_back(way);
								}
							
							}
					}

				}
		}
	}
};


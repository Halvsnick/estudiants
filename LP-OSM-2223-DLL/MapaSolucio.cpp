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

using namespace std;

class MapaSolucio : public MapaBase {
private:

	PuntInteresBotiga shop; 
	PuntInteresRestaurant restaurant;
	Coordinate coord; 
    
public:

	void getPdis(std::vector<PuntDeInteresBase*>&)
	{
		// crear LA BOTIGA 
		string shopTag = "bakery";
		string latitud = "41.4918606";
		string longitud = "2.1465411";
		std::string name = "La Millor Pastisseria";
		bool wheelchair = true;

		Coordinate coord;
		coord.lat = 41.4933070;
		coord.lon = 2.1453852;

		PuntDeInteresBase* newShop = new PuntInteresBotiga(coord, name, shopTag, wheelchair);
			
		// crear EL RESTAURANT 

		string TypeCuisine = "regional";
		latitud = "41.4902204";
		longitud = "2.1406477";
		name = "El Millor Restaurant";
		wheelchair = true;

		coord.lat = 41.4933070;
		coord.lon = 2.1453852;

		newShop = new PuntInteresRestaurant(coord, name, TypeCuisine, wheelchair);
	}
	
	void getCamins(std::vector<CamiBase*>&) {}
	void parsejaXmlElements(std::vector<XmlElement>& xmlElements) {}
};

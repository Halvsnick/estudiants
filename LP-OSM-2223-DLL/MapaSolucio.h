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
	void parsejaXmlElements(std::vector<XmlElement>& xmlElements) {}
};

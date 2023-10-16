#pragma once
#include "PuntDeInteresBase.h"
#include "Common.h"
#include <string>

using namespace std;

class PuntInteresRestaurant : public PuntDeInteresBase {
public:

	PuntInteresRestaurant() : m_typeCuisine(""), m_wheelchair(false) {};

	//contructor per parametres
	PuntInteresRestaurant(Coordinate coord, string name, unsigned int color, const string&typeCuisine, bool wheelchair) : 
		PuntDeInteresBase(coord, name) { m_typeCuisine = typeCuisine; m_wheelchair = wheelchair;};

	unsigned int getColor()
	{
		switch (m_wheelchair)
		{
		case 0:
			if (m_typeCuisine == "chinese")
				return 0xA6D9F7;

		case 1:
			if (m_typeCuisine == "pizza")
				return 0x03FCBA;
			if (m_typeCuisine == "chinese")
				return 0xA6D9F7;
			else return 0x251351;

		default:
			return PuntDeInteresBase::getColor();
		}
	}

	string getName() { return m_typeCuisine; }

private:
	string m_typeCuisine;
	bool m_wheelchair;
};



#pragma once
#include "PuntDeInteresBase.h"
#include "Common.h"
#include <string>

using namespace std;


class PuntInteresBotiga : public PuntDeInteresBase {
public:

	PuntInteresBotiga() : m_shopTag(""), m_wheelchair(false) {}; 

	//contructor per parametres
	PuntInteresBotiga(Coordinate coord, string name, const string& shopTag, bool wheelchair) :
		PuntDeInteresBase(coord, name) { m_shopTag = shopTag; m_wheelchair = wheelchair;};
	
	unsigned int getColor()
	{
		switch (m_wheelchair)
		{
		case 1:
			if (m_shopTag == "bakery")
				if (getName().find("“Div 06:00-22:00") != string::npos
					|| getName().find("Dill 06:00-22:00") != string::npos)
					return 0x4CB944;
				else
					return 0xE85D75; 
		default:
			if (m_shopTag == "supermarket")
				return 0xA5BE00;
			else if (m_shopTag == "tobacco")
					return 0xFFAD69;
				else if (m_shopTag == "bakery")
						return 0xE85D75;
					else
						return 0xEFD6AC;
		}
	}

	string getName() { return m_shopTag; }

private:
	string m_shopTag;
	bool m_wheelchair;
};







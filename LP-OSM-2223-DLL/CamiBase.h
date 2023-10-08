#pragma once

#include "Common.h"
#include <vector>

class CamiBase {  //clase virutal pura
	public:
		virtual std::vector<Coordinate> getCamiCoords() = 0;
};


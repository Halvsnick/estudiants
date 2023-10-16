#pragma once
#include "PuntDeInteresBase.h"
#include "Common.h"
#include <string>

class PuntInteresBotiga : public PuntDeInteresBase {
public:
    PuntInteresBotiga(Coordinate coord, std::string name, unsigned int color);

    unsigned int getColor() override;
    std::string PuntInteresBotiga::getName() {
        return PuntDeInteresBase::getName(); // Llama al m�todo getName de la clase base.
    }
};




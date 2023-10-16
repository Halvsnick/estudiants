#pragma once
#include "PuntDeInteresBase.h"
#include "Common.h"
#include <string>

class PuntInteresRestaurant : public PuntDeInteresBase {
public:
    PuntInteresRestaurant(Coordinate coord, std::string name, unsigned int color);

    unsigned int getColor() override;
    std::string PuntInteresRestaurant::getName() {
        return PuntDeInteresBase::getName(); // Llama al método getName de la clase base.
    }
};


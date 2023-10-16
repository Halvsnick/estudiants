#pragma once

#include "Common.h"
#include <vector>
#include "CamiBase.h"

using namespace std;


class CamiSolucio : public CamiBase {
public:
    std::vector<Coordinate> getCamiCoords(int caminoSeleccionado); // Agafa les coordenades d'un camí específic
    std::vector<std::string> getCamins();  // Agafa tots els camins
};


std::vector<Coordinate> CamiSolucio::getCamiCoords(int caminoSeleccionado) {
    std::vector<Coordinate> coordenadas;

    // Por ejemplo, si caminoSeleccionado es 0, procesaríamos el primer camino en xmlElements.
    if (caminoSeleccionado >= 0 && caminoSeleccionado < XmlElement.size()) {
        const XmlElement& elemento = XmlElement[caminoSeleccionado];

        for (const auto& atributo : elemento.atributs) {
            if (atributo.first == "lat") {
                double lat = std::stod(atributo.second);
                double lon = 0.0; 
                for (const auto& atributoLon : elemento.atributs) {
                    if (atributoLon.first == "lon") {
                        lon = std::stod(atributoLon.second);
                        break;
                    }
                }
                coordenadas.push_back({ lat, lon });
            }
        }
    }

    return coordenadas;
}

std::vector<std::vector<Coordinate>> CamiSolucio::getCamins() {
    std::vector<std::vector<Coordinate>> caminos;

    for (const auto& elemento : XmlElement) {
        std::vector<Coordinate> coordenadas;

        for (const auto& atributo : elemento.atributs) {
            if (atributo.first == "lat") {
                double lat = std::stod(atributo.second);
                double lon = 0.0;
                for (const auto& atributoLon : elemento.atributs) {
                    if (atributoLon.first == "lon") {
                        lon = std::stod(atributoLon.second);
                        break;
                    }
                }
                coordenadas.push_back({ lat, lon });
            }
        }

        if (!coordenadas.empty()) {
            caminos.push_back(coordenadas);
        }
    }

    return caminos;
}



#pragma once
#include "Common.h"
#include "CamiBase.h"
#include <vector>

class CamiSolucio : public CamiBase {
public:
    std::vector<Coordinate> getCamiCoords() ;

    void getCamins(std::vector<CamiBase*>& caminos) {
        // Crea una instancia de CamiSolucio y agrega el camino al vector
        caminos.push_back(new CamiSolucio());
    }
};

// Tasca 4 crear cami definit 

std::vector<Coordinate> CamiSolucio::getCamiCoords() {
    std::vector<Coordinate> coordenadas;

    // Añadir las coordenadas al vector
    coordenadas.push_back({ 41.4928803, 2.1452381 });
    coordenadas.push_back({ 41.4929072, 2.1452474 });
    coordenadas.push_back({ 41.4933070, 2.1453852 });
    coordenadas.push_back({ 41.4939882, 2.1456419 });

    return coordenadas;
}


/////////////////////////////////////////////////////////////////////////


/*
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
*/


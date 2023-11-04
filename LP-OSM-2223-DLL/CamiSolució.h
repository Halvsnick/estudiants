#pragma once
#include "Common.h"
#include "CamiBase.h"
#include <vector>

using namespace std;

class CamiSolucio : public CamiBase {
public:
    CamiSolucio() {};
    CamiSolucio(vector<Coordinate>& Coord) {m_ways = Coord; };
    vector<Coordinate> getCamiCoords() { return m_ways; };

private:
    vector<Coordinate> m_ways; 
};

// Tasca 4 crear cami definit 
/*
std::vector<Coordinate> CamiSolucio::getCamiCoords() {
    std::vector<Coordinate> coordenadas;

    // Añadir las coordenadas al vector
    coordenadas.push_back({ 41.4928803, 2.1452381 });
    coordenadas.push_back({ 41.4929072, 2.1452474 });
    coordenadas.push_back({ 41.4933070, 2.1453852 });
    coordenadas.push_back({ 41.4939882, 2.1456419 });

    return coordenadas;
}
*/

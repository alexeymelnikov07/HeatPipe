// --------------- INCLUDES ----------------
// Headers
#include "../../include/core/node.hpp"

// Libraries
#include <vector>

// ----------------------------------------

void createMesh(std::vector<Node>& node, HeatPipe& pipe, int cells) {
    Node evap(0);
    evap.zone = Node::Zone::EVAPORATOR;
    node.push_back(evap);
    
    const double dx = pipe.adiabaticLength / cells;
    for (int i = 0; i < cells; ++i) {
        Node cell(pipe.evaporatorLength + i*dx);
        cell.zone = Node::Zone::ADIABATIC;
        node.push_back(cell);
    }

    Node cond(pipe.evaporatorLength + pipe.adiabaticLength);
    cond.zone = Node::Zone::CONDENSER;
    node.push_back(cond);
    
    node.shrink_to_fit();
}
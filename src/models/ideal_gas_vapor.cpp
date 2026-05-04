// --------------- INCLUDES ----------------
// Headers
#include "../../include/models/ideal_gas_vapor.hpp"
#include "../../include/utils/constants.hpp"
#include "../core/node.hpp"

// Libraries
#include <string>
#include <iostream>
#include <vector>

// ----------------------------------------

double IdealGasVapor::pressureGradient(std::vector<Node> node, double massFlowRate, const WorkingFluid& fluid, const HeatPipe& pipe) const {
    
    for (auto it = node.begin(); it<node.end(); it++){
        if ( (*it).zone == Node::Zone::CONDENSER ) {break;}
        // Объёмный расход в ячейке
        double volumeFlow = massFlowRate / fluid.rhoVap((*it).P_vapor);
        // Длинна ячейки
        double deltaX = 0;
        if ( (*(it)).zone == Node::Zone::EVAPORATOR ) {deltaX = (*(it+1)).x - pipe.evaporatorLength / 2;}
        else if ( (*(it+1)).zone == Node::Zone::CONDENSER ) {deltaX = pipe.totalLength - pipe.condenserLength / 2 - (*it).x;}
        else {deltaX = (*(it+1)).x - (*it).x;}
        // Радиус парового канала в 4 степени
        double R_deg4 = pipe.vaporCoreRadius*pipe.vaporCoreRadius*pipe.vaporCoreRadius*pipe.vaporCoreRadius;
        //Давление пара в следующей ячейке
        double P_next = (*it).P_vapor - 8 * volumeFlow * fluid.viscVap((*it).P_vapor) * deltaX / (constants::pi * R_deg4);
        (*(it+1)).P_vapor = P_next;
        // Температура пара в следующей ячейке
        double T_next = fluid.Tsat(P_next);
        (*(it+1)).T_vapor = T_next;
    }
}
// --------------- INCLUDES ----------------
// Headers
#include "../../include/models/vapor_model.hpp"
#include "../../include/core/working_fluid.hpp"
#include "../../include/utils/constants.hpp"

// Libraries
#include <iostream>

// ----------------------------------------

// Формула Пуазейля [Па]
double VaporModel::Poiseuille(double P0, double l, double massFlowRate, const HeatPipe& pipe){
    if (P0 < 612) {
        std::cout<<"In VaporModel::Poiseuille P0 less than 612 Pa"<<std::endl;
        exit(-1);
    }
    double rho = WorkingFluid::rhoVap(P0);
    double eta = WorkingFluid::viscVap(P0);
    double Q = massFlowRate / rho;
    double dP = 8 * Q * eta * l * constants::pi / (pipe.vaporCoreArea * pipe.vaporCoreArea);
    return dP;
}

// Заполнить градиент давления пара в сетке (начиная с испарителя)
void VaporModel::calcGradient(std::vector<Node>& node, double P_evap, double massFlowRate, const HeatPipe& pipe){
    for (auto it = node.begin(); it != node.end(); ++it){
        Node& cell = *it;
        if (cell.zone == Node::Zone::CONDENSER){
            continue;
        }

        Node& cellNext = *(it+1);

        if (cell.zone == Node::Zone::EVAPORATOR){
            cell.P_vapor = P_evap;
            cell.T_vapor = WorkingFluid::Tsat(P_evap);
        }

        double l; // Длина которую прошёл пар
        if (cellNext.zone == Node::Zone::CONDENSER){ l = pipe.totalLength - cell.x; }
        else {  l = cellNext.x - cell.x; }

        double dP = VaporModel::Poiseuille(cell.P_vapor, l, massFlowRate, pipe);
        double P_next = cell.P_vapor - dP;

        cellNext.P_vapor = P_next;
        cellNext.T_vapor = WorkingFluid::Tsat(P_next);
    }
}

// Расcчитать число Рейнольдса [-]
double VaporModel::Reynolds(double P0, double massFlowRate, const HeatPipe& pipe){
    if (P0 < 612) {
        std::cout<<"In VaporModel::Reynolds P0 less than 612 Pa"<<std::endl;
        exit(-1);
    }
    double rho = WorkingFluid::rhoVap(P0);
    double Q = massFlowRate / rho;
    double v = Q / pipe.vaporCoreArea;
    double eta = WorkingFluid::viscVap(P0);
    double Re = v * pipe.vaporCoreRadius * rho / eta;
    return Re;
}

// Заполнить числа Рейнольдса в сетке
void VaporModel::fillReynolds(std::vector<Node>& node, double P_evap, double massFlowRate, const HeatPipe& pipe){
    for (auto it = node.begin(); it != node.end(); ++it){
        Node& cell = *it;
        double Reynolds = VaporModel::Reynolds(cell.P_vapor, massFlowRate, pipe);
        cell.Reynolds = Reynolds;
    }
}
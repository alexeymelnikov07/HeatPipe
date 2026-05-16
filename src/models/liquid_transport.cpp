// --------------- INCLUDES ----------------
// Headers
#include "../../include/models/liquid_transport.hpp"
#include "../../include/core/working_fluid.hpp"
#include "../../include/utils/constants.hpp"

// Libraries

// ----------------------------------------

// Закон Дарси [Па](Разность P0 - P(x+l))
double LiquidTransport::Darcy(double P0, double l, double massFlowRate, const HeatPipe& pipe){
    if (P0 < 612) {
        std::cout<<"In LiquidTransport::Darcy P0 less than 612 Pa"<<std::endl;
        exit(-1);
    }
    double rho = WorkingFluid::rhoLiq(P0);
    double Q = massFlowRate / rho;
    double eta = WorkingFluid::viscLiq(P0);
    double dP = Q * eta * l / pipe.wickCrossSection / pipe.wickPermeability;
    return dP;
}

// Заполнить градиент давления жидкости в сетке
void LiquidTransport::calcGradient(std::vector<Node>& node, double P_cond, double massFlowRate, const HeatPipe& pipe){
    for (auto it = node.rbegin(); it != node.rend(); ++it){
        Node cell = *it;
        
        if (cell.zone == Node::Zone::EVAPORATOR){
            continue;
        }

        Node cellNext = *(it+1);

        if (cell.zone == Node::Zone::CONDENSER){
            cell.P_liquid = P_cond;
            cell.T_liquid = cell.T_vapor;
        }

        double l;
        if (cell.zone == Node::Zone::CONDENSER) { l = pipe.totalLength - cellNext.x; }
        else { l = cell.x - cellNext.x; }

        double dP = LiquidTransport::Darcy(cell.P_liquid, l, massFlowRate, pipe );
        double P_next = cell.P_liquid - dP;

        cellNext.P_liquid = P_next;
        cellNext.T_liquid = cellNext.T_vapor;
    }
}

// Предельное капиллярное давление по формуле Лапласа [Па]
double LiquidTransport::capillaryMaxPressure(double T_evap, const HeatPipe& pipe){
    double sigma = WorkingFluid::sigma(T_evap);
    double dP = 2 * sigma / pipe.wickEffectiveRadius;
    return dP;
}
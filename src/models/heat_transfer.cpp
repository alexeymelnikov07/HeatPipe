// --------------- INCLUDES ----------------
// Headers
#include "../../include/models/heat_transfer.hpp"
#include "../../include/core/working_fluid.hpp"
#include "../../include/utils/constants.hpp"

// Libraries
#include <cmath>

// ----------------------------------------

// Тепловой поток через стенку и фитиль с жидкостью(цилиндрический закон Фурье) [Вт/м^2]
double HeatTransfer::heatFlux(double T_out, double T_vap, double l, const HeatPipe& pipe){
    double P_vap = WorkingFluid::Psat(T_vap);
    double k_liq = WorkingFluid::tcondLiq(P_vap);
    double k_wall = pipe.pipeThermalConductivity;
    double k_met = pipe.wickThermalConductivity;
    double e = pipe.wickPorosity;
    // Формула Максвелла для теплопроводности металлического порошка с жидкостью внутри
    double k_eff = k_met * ( 2*k_met + k_liq - 2*e*(k_met-k_liq) ) / ( 2*k_met + k_liq + e*(k_met-k_liq) );

    double r1 = pipe.vaporCoreRadius + pipe.wickThickness + pipe.wallThickness;
    double r2 = pipe.vaporCoreRadius + pipe.wickThickness;
    double r3 = pipe.vaporCoreRadius;

    double R_wall = std::log(r1/r2) / ( 2 * constants::pi * k_wall * l );
    double R_wick = std::log(r2/r3) / ( 2 * constants::pi * k_eff * l );
    double R_total = R_wall + R_wick;

    double heatFlux = ( T_out - T_vap ) / R_total;

    return heatFlux;
}

// Массовый расход рабочего тела [кг/с]
double HeatTransfer::massFlowRate(double T_vap, double heatFlux){
    double P_vap = WorkingFluid::Psat(T_vap);
    double lambda =  WorkingFluid::lambda(P_vap);
    double massFlowRate = heatFlux / lambda;
    return massFlowRate;
}
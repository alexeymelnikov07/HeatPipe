// --------------- INCLUDES ----------------
// Headers
#include "../../include/core/thermal_solver.hpp"

// Libraries
#include <cmath>
#include <array>

// ----------------------------------------

// Запуск расчёта пара: испаритель -> градиент пара -> конденсатор, с записью результата
void ThermalSolver::launchVaporAttempt(double T_evap, calculationResult& res){
    double heatFlux_evap = HeatTransfer::heatFlux(BC.T_evap_out, T_evap, Pipe.evaporatorLength, Pipe);
    double massFlowRate = HeatTransfer::massFlowRate(T_evap, heatFlux_evap);

    double P_evap = WorkingFluid::Psat(T_evap);
    VaporModel::calcGradient(Mesh, P_evap, massFlowRate, Pipe);

    /* Ловим экспешон ??? */
    
    double T_cond = Mesh.back().T_vapor;
    double heatFlux_cond = HeatTransfer::heatFlux(BC.T_cond_out, T_cond, Pipe.condenserLength, Pipe);

    res.heatFlux_evap = heatFlux_evap;
    res.heatFlux_cond = heatFlux_cond;
    res.massFlowRate = massFlowRate;
    res.T_cond = T_cond;
}

// Запуск расчёта жидкости: закон Дарси -> капилярный предел, с записью результата
void ThermalSolver::launchLiquidAttempt(double T_evap, calculationResult& res){
    LiquidTransport::calcGradient(Mesh, Mesh.back().P_vapor, res.massFlowRate, Pipe);

    /* Ловим экспешон ??? */

    double dP_maxCapilar = LiquidTransport::capillaryMaxPressure(T_evap, Pipe);
    double dP_liq = Mesh.back().P_liquid - Mesh.front().P_liquid;

    res.dP_maxCapilar = dP_maxCapilar;
    res.dP_liq = dP_liq;
}

// Поиск значения температуры пара в испарителе с заданным шагом
std::array<double, 2> ThermalSolver::temperatureGuess(double step, std::array<double, 2> borders , std::vector<calculationResult>& calcResults){
    double T_evap_max = borders[0] + step;
    double T_evap_min = borders[1] + step;

    std::array<double, 2> tempGuesses;
    tempGuesses[0] = borders[0];
    tempGuesses[1] = borders[1];
    bool firstIsGuessed = false;

    for(double T_evap = T_evap_max; T_evap >T_evap_min; T_evap -= step){
        calculationResult res(T_evap);
        
        launchVaporAttempt(T_evap, res);

        /* Ловим эксепшон ??? */
        
        double tolerance = (1 - std::abs( res.heatFlux_cond / res.heatFlux_evap ) ) * 100;
        if (res.T_cond < BC.T_cond_out) {
            res.isVaporOkay = false;
        }
        else if (tolerance < 0){
            res.isVaporOkay = false;
        }
        else if (tolerance > BC.modelTolerance ){
            res.isVaporOkay = false;
        }
        else { res.isVaporOkay = true; }

        if (res.isVaporOkay){
            launchLiquidAttempt(T_evap, res);

            /* Ловим эксепшон ??? */

            if (res.dP_liq < 0 || res.dP_maxCapilar < 0){
                res.isLiquidOkay = false;
            }
            else if (res.dP_liq > res.dP_maxCapilar){
                res.isLiquidOkay = false;
            }
            else { res.isLiquidOkay = true; }
        }
        calcResults.push_back(res);

        if ( !firstIsGuessed && res.isVaporOkay && res.isLiquidOkay){
            tempGuesses[0] = T_evap;
            firstIsGuessed = true;
        }
        else if ( firstIsGuessed && res.isVaporOkay && res.isLiquidOkay){
            tempGuesses[1] = T_evap;
        }
        else if ( firstIsGuessed && ( !res.isVaporOkay || !res.isLiquidOkay ) ){
            break;
        }
    }
    return tempGuesses;
}

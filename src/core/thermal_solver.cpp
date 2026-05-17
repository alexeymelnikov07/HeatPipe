// --------------- INCLUDES ----------------
// Headers
#include "../../include/core/thermal_solver.hpp"

// Libraries
#include <cmath>
#include <array>

namespace {

    constexpr double kHeatFluxEpsilon = 1e-12;

    // Относительное расхождение мощностей [%]: 0 — идеальный баланс Q_evap и Q_cond
    double heatBalanceTolerancePercent(double Q_evap, double Q_cond) {
        if (std::abs(Q_evap) < kHeatFluxEpsilon) {
            return -1.0;
        }
        return (1.0 - std::abs(Q_cond / Q_evap)) * 100.0;
    }

}

ThermalSolver::ThermalSolver(const HeatPipe& pipe, const BoundaryConditions& bc, int meshCells)
    : Pipe(pipe), BC(bc) {
    createMesh(Mesh, Pipe, meshCells);
}

void ThermalSolver::launchVaporAttempt(double T_evap, calculationResult& res) {
    const double heatFlux_evap = HeatTransfer::heatFlux(BC.T_evap_out, T_evap, Pipe.evaporatorLength, Pipe);
    const double massFlowRate = HeatTransfer::massFlowRate(T_evap, heatFlux_evap);

    const double P_evap = WorkingFluid::Psat(T_evap);
    VaporModel::calcGradient(Mesh, P_evap, massFlowRate, Pipe);

    const double T_cond = Mesh.back().T_vapor;
    const double heatFlux_cond = HeatTransfer::heatFlux(BC.T_cond_out, T_cond, Pipe.condenserLength, Pipe);

    res.heatFlux_evap = heatFlux_evap;
    res.heatFlux_cond = heatFlux_cond;
    res.massFlowRate = massFlowRate;
    res.T_cond = T_cond;
}

void ThermalSolver::launchLiquidAttempt(double T_evap, calculationResult& res) {
    LiquidTransport::calcGradient(Mesh, Mesh.back().P_vapor, res.massFlowRate, Pipe);

    res.dP_maxCapillary = LiquidTransport::capillaryMaxPressure(T_evap, Pipe);
    // Жидкость течёт к области меньшего давления: перепад вдоль трубки от конденсатора к испарителю
    res.dP_liq = Mesh.back().P_liquid - Mesh.front().P_liquid;
}

std::array<double, 2> ThermalSolver::temperatureGuess(
    double step,
    std::array<double, 2> borders,
    std::vector<calculationResult>& calcResults) {
    const double T_evap_max = borders[0] + step;
    const double T_evap_min = borders[1] + step;

    std::array<double, 2> tempGuesses{borders[0], borders[1]};
    bool firstIsGuessed = false;

    for (double T_evap = T_evap_max; T_evap > T_evap_min; T_evap -= step) {
        calculationResult res(T_evap);

        launchVaporAttempt(T_evap, res);

        const double tolerance = heatBalanceTolerancePercent(res.heatFlux_evap, res.heatFlux_cond);

        if (T_evap <= BC.T_evap_out) {
            res.isVaporOkay = false;
        } else if (res.T_cond <= BC.T_cond_out) {
            res.isVaporOkay = false;
        } else if (tolerance < 0.0) {
            res.isVaporOkay = false;
        } else if (tolerance > BC.modelTolerance) {
            res.isVaporOkay = false;
        } else {
            res.isVaporOkay = true;
        }

        if (res.isVaporOkay) {
            launchLiquidAttempt(T_evap, res);

            if (res.dP_liq < 0.0 || res.dP_maxCapillary < 0.0) {
                res.isLiquidOkay = false;
            } else if (res.dP_liq > res.dP_maxCapillary) {
                res.isLiquidOkay = false;
            } else {
                res.isLiquidOkay = true;
            }
        } else {
            res.isLiquidOkay = false;
        }

        calcResults.push_back(res);

        if (!firstIsGuessed && res.isVaporOkay && res.isLiquidOkay) {
            tempGuesses[0] = T_evap;
            firstIsGuessed = true;
        } else if (firstIsGuessed && res.isVaporOkay && res.isLiquidOkay) {
            tempGuesses[1] = T_evap;
        } else if (firstIsGuessed && (!res.isVaporOkay || !res.isLiquidOkay)) {
            break;
        }
    }

    return tempGuesses;
}

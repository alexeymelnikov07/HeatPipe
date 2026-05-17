// Главный класс решения задачи переноса тепла
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "./heatpipe_params.hpp"
#include "./node.hpp"
#include "./working_fluid.hpp"
#include "../boundary/boundary_condition.hpp"
#include "../utils/calculation_result.hpp"

#include "../models/heat_transfer.hpp"
#include "../models/liquid_transport.hpp"
#include "../models/vapor_model.hpp"

// Libraries
#include <vector>
#include <array>

// ----------------------------------------

class ThermalSolver {
private:
    std::vector<Node> Mesh;
    HeatPipe Pipe;
    BoundaryConditions BC;

    // Одна попытка: испаритель -> Пуазейль по сетке -> конденсатор
    void launchVaporAttempt(double T_evap, calculationResult& res);

    // Одна попытка: Дарси от узла конденсатора назад, перепад жидкости и капиллярный предел
    void launchLiquidAttempt(double T_evap, calculationResult& res);

public:
    ThermalSolver(const HeatPipe& pipe, const BoundaryConditions& bc, int meshCells);

    // Перебор T_vap,e с шагом step в интервале borders; накопление попыток в calcResults
    std::array<double, 2> temperatureGuess(
        double step,
        std::array<double, 2> borders,
        std::vector<calculationResult>& calcResults
    );
};
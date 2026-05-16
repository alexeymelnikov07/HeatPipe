// Главный класс решения задачи переноса тепла
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "./heatpipe_params.hpp"
#include "./node.hpp"
#include "./working_fluid.hpp"
#include "../boundary/boundary_condition.hpp"
#include "../utils/constants.hpp"
#include "../utils//calculation_result.hpp"

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

public:
    // Запуск расчёта пара: испаритель -> градиент пара -> конденсатор, с записью результата
    void launchVaporAttempt(double T_evap, calculationResult& res);

    // Запуск расчёта жидкости: закон Дарси -> капилярный предел, с записью результата
    void launchLiquidAttempt(double T_evap, calculationResult& res);

    // Поиск значения температуры пара в испарителе с заданным шагом
    std::array<double, 2> temperatureGuess(double step, std::array<double, 2> borders,  std::vector<calculationResult>& calcResults);

};
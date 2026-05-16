// Основной класс описания пара
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../core/working_fluid.hpp"
#include "../core/heatpipe_params.hpp"
#include "../core/node.hpp"

// Libraries
#include <string>
#include <vector>

// ----------------------------------------

class VaporModel {
public:
    // Формула Пуазейля [Па]
    static double Poiseuille(double P0, double l, double massFlowRate, const HeatPipe& pipe);

    // Заполнить градиент давления пара в сетке (начиная с испарителя)
    static void calcGradient(std::vector<Node>& node, double P_evap, double massFlowRate, const HeatPipe& pipe);

    // Расчитать число Рейнольдса [-]
    static double Reynolds(double P0, double massFlowRate, const HeatPipe& pipe);

    // Заполнить числа Рейнольдса в сетке
    static void fillReynolds(std::vector<Node>& node, double P_evap, double massFlowRate, const HeatPipe& pipe);

};
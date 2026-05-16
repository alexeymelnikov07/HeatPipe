// Основной класс описания движения жидкости
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../core/heatpipe_params.hpp"
#include "../core/working_fluid.hpp"
#include "../core/node.hpp"

// Libraries
#include <string>

// ----------------------------------------

class LiquidTransport {
private:
    // Закон Дарси [Па](Разность P0 - P(x+l))
    static double Darcy(double P0, double l, double massFlowRate, const HeatPipe& pipe);

public:
    // Заполнить градиент давления жидкости в сетке
    static void calcGradient(std::vector<Node>& node, double P_cond, double massFlowRate, const HeatPipe& pipe);
    
    // Предельное капиллярное давление по формуле Лапласа [Па]
    static double capillaryMaxPressure(double T_evap, const HeatPipe& pipe);

};
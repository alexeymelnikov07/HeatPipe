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
    // P_liq на узле конденсатора, интеграция Дарси назад к испарителю
    static void calcGradient(std::vector<Node>& node, double P_cond, double massFlowRate, const HeatPipe& pipe);

    // Максимальный капиллярный перепад 2*sigma/r_eff [Па]
    static double capillaryMaxPressure(double T_evap, const HeatPipe& pipe);

};
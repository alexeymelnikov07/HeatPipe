// Основной класс описания переноса тепла в трубке
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../core/heatpipe_params.hpp"
#include "../core/working_fluid.hpp"

// Libraries
#include <string>

// ----------------------------------------

class HeatTransfer {
public:
    // Тепловая мощность Q через стенку и фитиль: T_out — T_ext, T_vap — T_sat [Вт]
    static double heatFlux(double T_out, double T_vap, double l, const HeatPipe& pipe);

    // Массовый расход m_dot = Q / r(T_vap) [кг/с]
    static double massFlowRate(double T_vap, double heatPower);

};
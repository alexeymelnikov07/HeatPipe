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
    // Тепловая мощность через стенку и фитиль с жидкостью(цилиндрический закон Фурье) [Вт]
    static double heatFlux(double T_out, double T_vap, double l, const HeatPipe& pipe);

    // Массовый расход рабочего тела [кг/с]
    static double massFlowRate(double T_vap, double heatFlux);

};
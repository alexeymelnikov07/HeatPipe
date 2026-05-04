// Основной класс описния переноса тепла в трубке
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../core/geometry.hpp"
#include "../core/heatpipe_params.hpp"
#include "../core/working_fluid.hpp"

// Libraries
#include <string>

// ----------------------------------------

class HeatTransfer {
public:
    // Тепловой поток через стенку и фитиль с жидкостью [Вт/м^2]
    virtual double heatFlux(double T_out, double T_vap, const Geomety& geomety, const HeatPipe& pipe) const = 0;

    // Массовый расход рабочего тела [кг/с]
    virtual double massFlowRate(double heatFlux, const WorkingFluid& fluid, const Geomety& geometry) const = 0;

    // Обозначение используемой модели
    virtual std::string name() const = 0;
};
// Основной класс описания пара
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../core/working_fluid.hpp"
#include "../core/heatpipe_params.hpp"
#include "../core/geometry.hpp"

// Libraries
#include <string>

// ----------------------------------------

class VaporModel {
public:
    // Рассчитать плотность пара [кг/м^3]
    virtual double density(double P, double T) const = 0;

    // Расчитать градиент давления пара [Па/м]
    virtual double pressureGradient(double massFlowRate, const WorkingFluid& fluid, const HeatPipe& pipe, const Geomety& geometry) const = 0;

    // Обозначение используемой модели
    virtual std::string name() const = 0;
};
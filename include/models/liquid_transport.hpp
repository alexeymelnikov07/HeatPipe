// Основной класс описания движения жидкости
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../core/heatpipe_params.hpp"
#include "../core/working_fluid.hpp"

// Libraries
#include <string>

// ----------------------------------------

class LiquidTransport {
public:
    // Градиент давления в адиабатической зоне фитиля [Па/м]
    virtual double pressureGradient(double massFlowRate, const WorkingFluid& fluid, const HeatPipe& pipe) const = 0;
    
    // Предельное капиллярное давление по формуле Лапласа [Па]
    double capillaryMaxPressure(const WorkingFluid& fluid, const HeatPipe& pipe) const;

    // Обозначение используемой модели
    virtual std::string name() const = 0;
};
// Основной класс описания движения жидкости
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../core/heatpipe_params.hpp"
#include "../core/working_fluid.hpp"

// Libraries
#include <string>
#include <iostream>

// ----------------------------------------

class LiquidTransport {
public:
    // Градиент давления в адиабатической зоне фитиля [Па/м]
    virtual double pressureGradient(double massFlowRate, const WorkingFluid& fluid, const HeatPipe& pipe) const = 0;
    
    // Предельное капиллярное давление по формуле Лапласа [Па]
    double capillaryMaxPressure(double P, const WorkingFluid& fluid, const HeatPipe& pipe);

    // Обозначение используемой модели
    virtual std::string name() const = 0;
};

double LiquidTransport::capillaryMaxPressure(double P, const WorkingFluid& fluid, const HeatPipe& pipe){
    return 2*fluid.sigma(P) / pipe.wickEffectiveRadius;
};
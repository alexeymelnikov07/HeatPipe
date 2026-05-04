// Закон Дарси - модель течения жидкости в капиляре
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../models/liquid_transport.hpp"

// Libraries
#include <string>

// ----------------------------------------

class DarcyFlow : public LiquidTransport {    
public:
    DarcyFlow(double sigma);
    
    // Градиент давления в адиабатической зоне фитиля по закону Дарси [Па/м]
    double pressureGradient(double massFlowRate, const WorkingFluid& fluid, const HeatPipe& pipe) const override;

    std::string name() const override {return "Darcy";}
};

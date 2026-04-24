// Закон Дарси - модель течения жидкости в капиляре
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../models/liquid_transport.hpp"

// Libraries
#include <string>

// ----------------------------------------

class DarcyFlow : public LiquidTransport {
    double surfaceTension;  // коэффициент поверхностного натяжения [Н/м]
    
public:
    DarcyFlow(double sigma);
    
    double massFlowRate() const override;
    double capillaryPressure() const override;

    std::string name() const override {return "Darcy";}
};

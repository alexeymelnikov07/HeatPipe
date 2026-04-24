// Модель идеального газа
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../models/vapor_model.hpp"

// Libraries
#include <string>

// ----------------------------------------

class IdealGasVapor: VaporModel{
    const double R_gas;         // Универсальная газовая постоянная [Дж/(кг*К)]
    const double Viscosity;     // Динамическая вязкость [Па*с]
public:
    IdealGasVapor(double R, double eta);

    double density() const override;
    double pressureGradient() const override;
    
    std::string name() const override {return "Ideal Gas";}
};
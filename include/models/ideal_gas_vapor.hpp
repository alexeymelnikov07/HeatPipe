// Модель идеального газа
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../models/vapor_model.hpp"

// Libraries
#include <string>

// ----------------------------------------

class IdealGasVapor: VaporModel{
public:
    IdealGasVapor(double R, double eta);

    // Рассчитать плотность пара [кг/м^3]
    double density(double P, double T) const override;

    // Расчитать градиент давления пара по формуле Пуазейля [Па/м]
    double pressureGradient(double massFlowRate, const WorkingFluid& fluid, const HeatPipe& pipe, const Geomety& geometry) const override;
    
    std::string name() const override {return "Ideal Gas";}
};
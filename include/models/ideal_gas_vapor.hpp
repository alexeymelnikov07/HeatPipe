// Модель идеального газа
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../models/vapor_model.hpp"

// Libraries
#include <string>
#include <vector>

// ----------------------------------------

class IdealGasVapor: VaporModel{
public:
    IdealGasVapor() {}

    // Расчитать градиент давления пара вдоль трубки [Па/м]
    double pressureGradient(std::vector<Node> node, double massFlowRate, const WorkingFluid& fluid, const HeatPipe& pipe) const override;
    
    std::string name() const override {return "Ideal Gas";}
};
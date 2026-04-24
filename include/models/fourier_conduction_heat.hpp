// Закон Фурье - описание теплопроводности
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../models/heat_transfer.hpp"

// Libraries
#include <string>

// ----------------------------------------

class ConductionHeat : public HeatTransfer {
public:
    double heatFlux() const override;
    std::string name() const override {return "Fourier-Conduction";}
};
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
    // Тепловой поток через стенку и фитиль с жидкостью [Вт/м^2]
    double heatFlux(double T_out, double T_vap, const HeatPipe& pipe) const override;

    // Массовый расход рабочего тела [кг/с]
    double massFlowRate(double heatFlux, const WorkingFluid& fluid) const override;

    std::string name() const override {return "Fourier-Conduction";}
};
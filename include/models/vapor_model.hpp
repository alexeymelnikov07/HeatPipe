// Основной класс описания пара
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../core/working_fluid.hpp"
#include "../core/heatpipe_params.hpp"
#include "../core/node.hpp"

// Libraries
#include <string>
#include <vector>

// ----------------------------------------

class VaporModel {
public:
    // Расчитать градиент давления(положителен, от конденсатора до испарителя) пара вдоль трубки [Па/м]
    virtual double pressureGradient(std::vector<Node> node, double massFlowRate, const WorkingFluid& fluid, const HeatPipe& pipe) const = 0;

    // Обозначение используемой модели
    virtual std::string name() const = 0;
};
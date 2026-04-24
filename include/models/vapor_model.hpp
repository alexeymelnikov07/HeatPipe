// Основной класс описания пара
#pragma once
// --------------- INCLUDES ----------------
// Headers
#include "../core/node.hpp"

// Libraries
#include <string>

// ----------------------------------------

class VaporModel {
/* Нужно обдумать совместимость для разных моделей газа */
public:
    // Рассчитать плотность пара [кг/м^3]
    virtual double density() const = 0;

    // Расчитать градиент давления в узлах [Па/м]
    virtual double pressureGradient() const = 0;

    // Обозначение используемой модели
    virtual std::string name() const = 0;
};
// Основной класс описания движения жидкости
#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries
#include <string>

// ----------------------------------------

class LiquidTransport {
/* Нужно обдумать совместимость для разных моделей газа */
public:
    // Массовый расход жидкости через фитиль [кг/с]
    virtual double massFlowRate() const = 0;
    
    // Максимальное капиллярное давление (предел)
    virtual double capillaryPressure() const = 0;

    // Обозначение используемой модели
    virtual std::string name() const = 0;
};
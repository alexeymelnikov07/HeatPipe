// Основной класс описния переноса тепла в трубке
#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries
#include <string>

// ----------------------------------------

class HeatTransfer {
/* Нужно обдумать совместимость для разных моделей газа */
public:
    // Тепловой поток через стенку и фитиль [Вт/м^2]
    virtual double heatFlux() const = 0;

    // Обозначение используемой модели
    virtual std::string name() const = 0;
};
// Структура параметров тепловой трубки
#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries

// ----------------------------------------

struct HeatPipe {
    const double wickPermeability; // Проницаемость материала фитиля [м^2]
    const double wickEffectiveRadius; // Радиус эквивалентного капиляра с одним мениском [м]
    const double wickThermalConductivity; // Теплопроводность материала фитиля [Дж/(м*с*К)]

    const double pipeThermalConductivity; // Теплопроводность материала трубки [Дж/(м*с*К)]

    HeatPipe(double k, double r, double wickKappa, double pipeKappa) 
    : wickPermeability(k), wickEffectiveRadius(r), wickThermalConductivity(wickKappa),
    pipeThermalConductivity(pipeKappa) {}
};

// Структура параметров тепловой трубки
#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries
#include <numbers>
// ----------------------------------------

struct HeatPipe {
    // ---------- Геометрия -----------
    const double totalLength;         // Полная длина трубки [м]
    const double evaporatorLength;    // Длина зоны испарения [м]
    const double condenserLength;     // Длина зоны конденсации [м]
    const double vaporCoreRadius;     // Радиус парового канала [м]
    const double wickThickness;       // Толщина фитиля [м]
    const double wallThickness;       // Толщина стенки [м]
    
    // Вычисляемые
    const double wickCrossSection;    // Площадь сечения фитиля [м^2]
    const double vaporCoreArea;       // Площадь парового канала [м^2]
    const double adiabaticLength;     // Длина адиабатической зоны [м]
    // --------------------------------
    // ------------ Физические свойства ----------
    const double wickPermeability;          // Проницаемость материала фитиля [м^2]
    const double wickEffectiveRadius;       // Радиус эквивалентного капиляра с одним мениском [м]
    const double wickThermalConductivity;   // Теплопроводность материала фитиля [Дж/(м*с*К)]

    const double pipeThermalConductivity;   // Теплопроводность материала трубки [Дж/(м*с*К)]
    // -------------------------------------------
    HeatPipe(
        double totalLength,
        double evaporatorLength,
        double condenserLength,
        double vaporCoreRadius,
        double wickThickness,
        double wallThickness,

        double wickPermeability,
        double wickEffectiveRadius,
        double wickThermalConductivity,
        double pipeThermalConductivity
    ) : totalLength(totalLength),
        evaporatorLength(evaporatorLength),
        condenserLength(condenserLength),
        vaporCoreRadius(vaporCoreRadius),
        wickThickness(wickThickness),
        wallThickness(wallThickness),
        
        wickPermeability(wickPermeability),
        wickEffectiveRadius(wickEffectiveRadius),
        wickThermalConductivity(wickThermalConductivity),
        pipeThermalConductivity(pipeThermalConductivity),
        
        wickCrossSection(std::numbers::pi * ( (vaporCoreRadius+wickThickness)*(vaporCoreRadius+wickThickness) - vaporCoreRadius*vaporCoreRadius )),
        vaporCoreArea(std::numbers::pi * vaporCoreRadius*vaporCoreRadius),
        adiabaticLength(totalLength-condenserLength-condenserLength) {}
};

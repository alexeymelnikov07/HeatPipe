// Геометрия трубки
#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries
#include <numbers>
// ----------------------------------------

struct Geomety {
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

    Geomety(double totL, double evL, double conL,
            double vapCR, double wickT, double wallT)
            : totalLength(totalLength), evaporatorLength(evL), condenserLength(conL),
            vaporCoreRadius(vapCR), wickThickness(wickT), wallThickness(wallT),
            wickCrossSection(std::numbers::pi * ( (vapCR+wickT)*(vapCR+wickT) - vapCR*vapCR )),
            vaporCoreArea(std::numbers::pi * vapCR*vapCR), adiabaticLength(totL-evL-conL) {}
    // Geomety(): Geomety(0, 0, 0, 0, 0, 0) {}
};
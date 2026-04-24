#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries

// ----------------------------------------

struct BoundaryConditions {
    const double T_evaporator;     // Температура стенки испарителя [K]
    const double T_condenser;      // Температура стенки конденсатора [K]
    const double heatInput;        // Подводимая тепловая мощность [Вт]

    BoundaryConditions(double T_ev, double T_con, double heatI)
    : T_evaporator(T_ev), T_condenser(T_con), heatInput(heatI) {};
};
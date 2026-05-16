#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries

// ----------------------------------------

struct BoundaryConditions {
    const double T_evap_out;        // Температура стенки испарителя [K]
    const double T_cond_out;        // Температура стенки конденсатора [K]

    const double modelTolerance;    // Сходимость модели [%] (не учтённые потери тепла)

    BoundaryConditions(double T_evap, double T_cond, double modelTolerance)
    : T_evap_out(T_evap), T_cond_out(T_cond), modelTolerance(modelTolerance) {};
};
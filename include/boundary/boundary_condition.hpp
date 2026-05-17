#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries

// ----------------------------------------

struct BoundaryConditions {
    const double T_evap_out;     // Температура внешней среды у испарителя T_ext,e [K]
    const double T_cond_out;     // Температура внешней среды у конденсатора T_ext,c [K]

    // Допустимое относительное расхождение |Q_evap - Q_cond| в процентах
    const double modelTolerance;

    BoundaryConditions(double T_evap, double T_cond, double modelTolerance)
        : T_evap_out(T_evap),
          T_cond_out(T_cond),
          modelTolerance(modelTolerance) {}
};

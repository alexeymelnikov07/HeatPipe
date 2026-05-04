// Сетка разбиения
#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries

// ----------------------------------------

struct Node {
    const double x;     // Позиция вдоль оси [м]
    double T_wall;      // Температура стенки [K]
    double T_vapor;     // Температура пара [K]
    double P_vapor;     // Давление пара [Па]
    double P_liquid;    // Давление жидкости в фитиле [Па]
    double rho_vapor;   // Плотность пара [кг/м^3]
    
    // Фаза узла
    enum class Zone { EVAPORATOR, ADIABATIC, CONDENSER };
    Zone zone;
};
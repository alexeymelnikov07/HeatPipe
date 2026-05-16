// Сетка разбиения
#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries

// ----------------------------------------

struct Node {
    const double x;     // Позиция вдоль оси [м]
    double T_vapor;     // Температура пара [K]
    double P_vapor;     // Давление пара [Па]
    double T_liquid;    // Температура жидкости в фитиле [K] (ей равна температура стенки)
    double P_liquid;    // Давление жидкости в фитиле [Па]
    double Reynolds;    // Число Рейнольдса
    
    // Фаза узла
    enum class Zone { EVAPORATOR, ADIABATIC, CONDENSER, UNDEFINED };
    Zone zone;

    bool operator== (const Node& node) const {
        return x == node.x && zone == node.zone;
    }

    bool operator< (const Node& node) const {
        return x<node.x;
    }
    Node(double x): x(x) {
        P_vapor=0;
        T_vapor=0;
        T_liquid=0;
        P_liquid=0;
        Reynolds=0;
        zone = Zone::UNDEFINED;
    }
};
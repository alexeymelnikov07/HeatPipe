// Структура результатов попытки расчёта термотрубки
#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries
#include <cmath>

// ----------------------------------------

namespace calcRes_doubleComp {
    inline constexpr double doubleComp = 0.0005;
}

struct calculationResult {
    const double T_evap;        // Заданная температура пара в испарителе

    // Расчёты пара
    double T_cond;              // Найденая температура пара в конденсаторе
    double heatFlux_evap;       // Тепловая мощность через стенку в испарителе
    double heatFlux_cond;       // Тепловая мощность через стенку в конденсаторе
    double massFlowRate;        // Массовый расход
    bool isVaporOkay;           // Результат расчёта пара

    // Расчёты жидкости
    double dP_liq;              // Перепад давления в жидкости
    double dP_maxCapilar;       // Капилярный предел
    bool isLiquidOkay;          // Результат расчёта жидкости

    calculationResult(double T_evap): T_evap(T_evap) {
        T_cond = 0;
        heatFlux_evap = 0;
        heatFlux_cond = 0;
    }

    bool operator== (const calculationResult res) const {
        return std::abs(T_evap - res.T_evap) < calcRes_doubleComp::doubleComp;
    }

    bool operator< (const calculationResult res) const {
        return T_evap < res.T_evap;
    }
};
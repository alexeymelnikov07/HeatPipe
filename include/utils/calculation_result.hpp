// Структура результатов одной попытки расчёта
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
    const double T_evap;        // Пробная температура насыщения пара в испарителе [K]

    // Пар
    double T_cond;              // Температура насыщения пара у узла конденсатора [K]
    double heatFlux_evap;       // Тепловая мощность в зоне испарения [Вт]
    double heatFlux_cond;       // Тепловая мощность в зоне конденсации [Вт]
    double massFlowRate;        // Массовый расход [кг/с]
    bool isVaporOkay;           // Прошла проверку теплового баланса и T_vap > T_out

    // Жидкость
    double dP_liq;              // P_liq(конденсатор) - P_liq(испаритель) [Па], вдоль потока к меньшему p
    double dP_maxCapillary;     // Допустимый капиллярный перепад по Лапласу [Па]
    bool isLiquidOkay;          // dP_liq в пределах капиллярного предела

    explicit calculationResult(double T_evap)
        : T_evap(T_evap),
          T_cond(0),
          heatFlux_evap(0),
          heatFlux_cond(0),
          massFlowRate(0),
          isVaporOkay(false),
          dP_liq(0),
          dP_maxCapillary(0),
          isLiquidOkay(false) {}

    bool operator==(const calculationResult& other) const {
        return std::abs(T_evap - other.T_evap) < calcRes_doubleComp::doubleComp;
    }

    bool operator<(const calculationResult& other) const {
        return T_evap < other.T_evap;
    }
};

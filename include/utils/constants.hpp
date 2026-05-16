// Различные константы
#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries
#include <numbers>
// ----------------------------------------

namespace constants {
    // Математические константы
    inline constexpr double pi = std::numbers::pi;
    inline constexpr double e = std::numbers::e;
    
    // Физические константы
    inline constexpr double R = 8.314462; // Универсальная газовая постоянная [Дж/(моль*К)]
    inline constexpr double k = 1.380649e-23; // Константа Больцмана [Дж/К]
    inline constexpr double N_avogadro = 6.0221406e23; // Число Авогадро [1/моль]
}
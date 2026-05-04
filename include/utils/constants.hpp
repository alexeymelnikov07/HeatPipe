// Различные константы
#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries
#include <numbers>
// ----------------------------------------

namespace constants{
    // Математические константы
    double pi = std::numbers::pi;
    double e = std::numbers::e;
    
    // Физические константы
    double R = 8.314462; // Универсальная газовая постоянная [Дж/(моль*К)]
    double k = 1.380649e-23; // Константа Больцмана [Дж/К]
    double N_avogadro = 6.0221406e23; // Число Авогадро [1/моль]
}
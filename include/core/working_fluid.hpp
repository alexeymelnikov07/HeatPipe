// Основной класс описания жидкости
#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries
#include <map>
#include <string>

// ----------------------------------------

class WorkingFluid {
    /* Тут теплота фазового перехода и вязкость берутся при температуре зоны конденсации(хотя
    они существенно ЗАВИСЯТ ОТ ТЕМПЕРАТУРЫ). При вычислении давления насыщенных паров 
    используется модель ИДЕАЛЬНОГО ГАЗА. */
    /* Для улучшения модели можно загнать теплоту ф.п. и вязкость в зависимости от температуры
    в словарь(map) и искать ближайшее по температуре значение. */

    std::string name;
    const double molarMass;           // Молярная масса [кг/моль]
    const double latentHeat;          // Скрытая теплота фазового перехода [Дж/кг]
    const double Viscosity;     // Динамическая вязкость жидкости [Па*с]
    
    // Вычисленные значения давления насыщенных паров при данной температуре (кэш)
    std::map<double, double> saturationCache;
    
public:
    WorkingFluid(const std::string& name, double M, double L, double eta);
    WorkingFluid(): WorkingFluid("Empty", 0, 0, 0) {};
    // Давление насыщения при температуре
    double saturationPressure(double T) const;
    
    // Геттеры
    double getLatentHeat() const { return latentHeat; }
    double getViscosity() const { return Viscosity; }
    double getMolarMass() const { return molarMass; }
    const std::string& getName() const { return name; }
    
    // Очистить кеш
    void clearCache() { saturationCache.clear(); }
};
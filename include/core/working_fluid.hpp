// Основной класс описания рабочего тела трубки
#pragma once
// --------------- INCLUDES ----------------
// Headers

// Libraries
#include <map>
#include <string>
#include "IF97.h"

// ----------------------------------------

class WorkingFluid {
public:
    // Давление насыщения по температуре [Па]
    static double Psat(double T) {return IF97::psat97(T);}
    // Температура насыщения по давлению [К]
    static double Tsat(double P) {return IF97::Tsat97(P);}

    // Свойства жидкости и пара в насыщенном состоянии (на кривой равновесия фаз)
    //      --------------------
    // Плотность жидкости по давлению
    static double rhoLiq(double P) {return IF97::rholiq_p(P);}
    // Плотность пара по давлению
    static double rhoVap(double P) {return IF97::rhovap_p(P);}
    // Динамическая вязкость жидкости по давлению
    static double viscLiq(double P) {return IF97::viscliq_p(P);}
    // Динамическая вязкость пара по давлению
    static double viscVap(double P) {return IF97::viscvap_p(P);}
    // Теплопроводность жидкости по давлению
    static double tcondLiq(double P) {return IF97::tcondliq_p(P);}
    // Теплопроводность пара по давлению
    static double tcondVap(double P) {return IF97::tcondvap_p(P);}
    //      --------------------

    // Поверхностное натяжение жидкости по температуре
    static double sigma(double T) {return IF97::sigma97(T);}
    // Скрытая теплота перехода жидкость-пар
    static double lambda(double P) {return IF97::hvap_p(P)-IF97::hliq_p(P);}
};
#define USER_SOURCE
#include <profiler.h>
#include "Potencia.h"
#include <iostream>
#include <cmath>

Potencia::Potencia() {
    std::cout << "Calculadora de potencias inicializada." << std::endl;
}

Potencia::~Potencia() {
    std::cout << "Calculadora de potencias finalizada." << std::endl;
}

void Potencia::operadorPotencia(punteroPotencia a, punteroPotencia b, char operando) {
    if (operando == '^') {
        *a = std::pow(*a, *b);
        std::cout << "Resultado de la potencia: " << *a << std::endl;
    }
    else {
        std::cout << "Operador no v�lido para potencia." << std::endl;
    }
}
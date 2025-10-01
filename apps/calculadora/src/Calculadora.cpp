///<Summary>
///Se define la clase de calculadora, y la lógica de los métodos
///<Summary>

#include "../include/Calculadora.h"
#include <iostream>

Calculadora::Calculadora() = default;
Calculadora::~Calculadora() = default;

void Calculadora::operacion(punteroBasico a, punteroBasico b, char simbolo)
{
    switch (simbolo)
    {
    case '+': *a += *b; break;
    case '-': *a -= *b; break;
    case '*': *a *= *b; break;
    case '/':
        if (*b != 0) *a /= *b;
        else std::cout << "No se pueden hacer divisiones entre 0";
        break;
    default:
        std::cout << "El simbolo ingresado no es válido";
    }
    std::cout << "El resultado es: " << *a << std::endl;
}

void Calculadora::agregarMemoriaArray(punteroArray arreglo, punteroBasico elemento, std::size_t* indice)
{
    if (*indice < 100000) // Tamaño fijo del arreglo
    {
        arreglo[*indice] = *elemento;
        (*indice)++;
    }
}
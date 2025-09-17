///<Summary>
///Se define la clase de calculadora, y la l�gica de los m�todos
///<Summary>

#include "Calculadora.h"
#include <iostream>

Calculadora::Calculadora() = default;
Calculadora::~Calculadora() = default;

void Calculadora::operaci�n(punteroBasico a, punteroBasico b, char s�mbolo)
{
    switch (s�mbolo)
    {
    case '+': *a += *b; break;
    case '-': *a -= *b; break;
    case '*': *a *= *b; break;
    case '/':
        if (*b != 0) *a /= *b;
        else std::cout << "No se pueden hacer diviciones entre 0";
        break;
    default:
        std::cout << "El simbolo ingresado no es v�lido";
    }
    std::cout << "El resultado es: " << *a;
}

void Calculadora::agregarMemoriaArray(punteroArray arreglo, punteroBasico elemento, std::size_t* indice)
{
    if (*indice < 100000) // Tama�o fijo del arreglo
    {
        arreglo[*indice] = *elemento;
        (*indice)++;
    }
}
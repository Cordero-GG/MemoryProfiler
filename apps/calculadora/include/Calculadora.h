#ifndef PROYECTOMEMORIA_CALCULADORA_H
#define PROYECTOMEMORIA_CALCULADORA_H

#include <cstddef>

typedef double* punteroArray; // Puntero a un arreglo de doubles
typedef double* punteroBasico; // Es un "sin�nimo" de puntero, lo uso para hacerlo m�s legible

class Calculadora {
public:
    Calculadora();
    ~Calculadora(); // Destructor
    void operacion(punteroBasico a, punteroBasico b, char simbolo);
    void agregarMemoriaArray(punteroArray arreglo, punteroBasico elemento, std::size_t* indice);
};

#endif //PROYECTOMEMORIA_CALCULADORA_H
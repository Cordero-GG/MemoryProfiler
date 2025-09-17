#ifndef PROYECTOMEMORIA_CALCULADORA_H
#define PROYECTOMEMORIA_CALCULADORA_H

#include <cstddef>

typedef double* punteroArray; // Puntero a un arreglo de doubles
typedef double* punteroBasico; // Es un "sin�nimo" de puntero, lo uso para hacerlo m�s legible

class Calculadora {
public:
    Calculadora();
    ~Calculadora(); // Este es el destructor, libera recursos cuando se destruye el objeto
    void operaci�n(punteroBasico a, punteroBasico b, char s�mbolo);
    void agregarMemoriaArray(punteroArray arreglo, punteroBasico elemento, std::size_t* indice);
};

#endif //PROYECTOMEMORIA_CALCULADORA_H
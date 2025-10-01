#ifndef PROYECTOMEMORIA_POTENCIA_H
#define PROYECTOMEMORIA_POTENCIA_H

typedef double* punteroPotencia;

class Potencia {
public:
    Potencia();
    ~Potencia();
    void operadorPotencia(punteroPotencia a, punteroPotencia b, char operando);
};

#endif //PROYECTOMEMORIA_POTENCIA_H
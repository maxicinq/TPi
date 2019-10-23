#ifndef SOLUCION_AUXILIARES_H
#define SOLUCION_AUXILIARES_H

#include "definiciones.h"

#endif //SOLUCION_AUXILIARES_H

bool esImgValida(const imagen &A);

bool esMatriz(const imagen &A);

bool vacia(const imagen &A);

bool esBinaria(const imagen &A);

bool estanConectados(const imagen &A, const pixel &p, const pixel &q, const int &k);

float calcularPromedioDeAreas(const imagen &A, const int k);

bool esPixelContorno(const pixel &p, const imagen &A, const int &k);

imagen dilatar(const imagen &A, const imagen &B);

imagen erosionar(const imagen &A, const imagen &B);


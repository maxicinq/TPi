#ifndef SOLUCION_AUXILIARES_H
#define SOLUCION_AUXILIARES_H

#include "definiciones.h"

#endif //SOLUCION_AUXILIARES_H

bool activado(const pixel &p, const imagen &A);

bool pixelEnRango(const pixel &p, const imagen &A);

bool pixelValidoEncendido(const pixel &p, const imagen &A);

bool esMatriz(const imagen &A);

bool esBinaria(const imagen &A);

bool estanConectados(const imagen &A, const pixel &p, const pixel &q, const int &k);

sqPixel obtenerAdyacentes(const pixel &p, const imagen &A, const int &k);

bool pertenece(const pixel &p, const sqPixel &s);

float calcularPromedioDeAreas(const imagen &A, const int k);

vector<sqPixel> obtenerTodasLasRegiones(const imagen &A, const int &k);

sqPixel obtenerRegion(const imagen &A, const pixel &p, const int &k);

bool contenida(const sqPixel &sq, const vector<sqPixel> &s);

int apariciones(const pixel &p, const sqPixel &s);

bool esPixelContorno(const pixel &p, const imagen &A, const int &k);

bool tocaConBackground(const pixel &p, const imagen &A, const int &k);

bool estaEnBorde(const pixel &p, const imagen &A, const int &k);

imagen dilatar(const imagen &A, const imagen &B);

bool esPixelDeDilatacion(const imagen &A, const imagen &B, pixel p);

sqPixel estructuranteCentradoEn(const imagen &A, const imagen &B, pixel p);

imagen erosionar(const imagen &A, const imagen &B);

bool esPixelDeErosion(const imagen &A, const imagen &B, const pixel &p);

imagen intersecar(const imagen &A, const imagen &B);

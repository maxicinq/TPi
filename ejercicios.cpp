#include "definiciones.h"
#include "ejercicios.h"
#include "auxiliares.h"

// Ejercicio 1

bool esImagenValida(const imagen& img) {
    bool resp = esImgValida(img);

    return resp;
}

// Ejercicio 2

bool sonPixelesConectados(const imagen& img, const pixel& p, const pixel& q, int k) {
	bool resp = estanConectados(img, p, q, k);

    return resp;
}

// Ejercicio 3

float devolverPromedioAreas(const imagen &A, int k){
	float prom = -1.0;
	prom = calcularPromedioDeAreas(A,k);

    return prom;
}

// Ejercicio 4

sqPixel calcularContorno(const imagen &A, int k){
    sqPixel edges = {};

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            if (esPixelContorno({i,j},A,k)){
                edges.push_back({i,j});
            }
        }
    }

    return edges;
}

// Ejercicio 5

void cerrarForma(imagen &A, const imagen &B){
	closing(A, B);
}

// Ejercicio 6

int obtenerRegionConectada(imagen &A, const pixel &semilla) {
	int ite = obtenerRegionContando(A, semilla, 8);
	return ite;
}




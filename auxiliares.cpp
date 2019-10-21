//
//
#include <cstdlib>
#include "definiciones.h"
#include "auxiliares.h"

using namespace std;

bool esImgValida(const imagen &A){
    bool result = !vacia(A) && esMatriz(A) && esBinaria(A);
    return result;
}

bool esMatriz(const imagen &A){
    bool result = true;

    if (A.empty()){
        result = false;
    } else if (A[0].empty()){
        result = false;
    }

    for (int i = 0; i < A.size() - 1 && result; i++) {
        if(A[i].size() != A[i+1].size()){
            result = false;
        }
    }
    return result;
}

bool vacia(const imagen &A){
    bool result = false;

    if(A.empty()){
        result = true;
    }
    return result;
}

bool esBinaria(const imagen &A){
    bool result = true;

    for (int i = 0; i < A.size() && result; i++) {
        for (int j = 0; j < A[i].size() && result; j++) {
            if(A[i][j] != 0 && A[i][j] != 1){
                result = false;
            }
        }
    }
    return result;
}

bool activado(const pixel &p, const imagen &A){
    return A[p[0]][p[1]] == 1;
}

bool pixelEnRango(const pixel &p, const imagen &A){
    return (p[0] >= 0 && p[0] < A.size() && p[1] >= 0 && p[1] < A.size());
}

bool pixelValidoEncendido(const pixel &p, const imagen &A){

}

bool estanConectados(const pixel &p, const pixel &q, const imagen &A, const int &k){
    bool result = false;

    if (k == 4 && pixelEnRango(p,A) && pixelEnRango(q,A) && activado(p,A) && activado(q,A)){
        result = abs(p[0] - q[0]) + abs(p[1] - q[1]) <= 1;
    } else if (k == 8 && pixelEnRango(p,A) && pixelEnRango(q,A) && activado(p,A) && activado(q,A)){
        result = max(abs(p[0] - q[0]), abs(p[1] - q[1])) <= 1;
    }
}

bool pertenece(const pixel &p, const sqPixel &s){
    bool result = false;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == p){
            result = true;
        }
    }
    return result;
}

sqPixel obtenerAdyacentes(const pixel &p, const imagen &A, const int &k){
    sqPixel result = {};
    if (k == 4){
        result = {{p[0]-1,p[1]}, {p[0]+1,p[1]}, {p[0],p[1]-1}, {p[0],p[1]+1}};
    } else if (k == 8){
        result = {{p[0]-1,p[1]}, {p[0]+1,p[1]}, {p[0],p[1]-1}, {p[0],p[1]+1},
                {p[0]-1,p[1]-1}, {p[0]-1,p[1]+1}, {p[0]+1,p[1]-1}, {p[0]+1,p[1]+1}};
    }
    return result;
}

bool estanConectados(const imagen &A, const pixel &p, const pixel &q, const int &k){
    sqPixel obtenidos = {p};
    sqPixel obtenidosAnt = {p};
    sqPixel adyacentes = {};
    sqPixel tmp = {};
    sqPixel tmpAnt = {p};

    for (int i = 0; i < tmpAnt.size(); i++) {
        adyacentes = obtenerAdyacentes(tmpAnt[i], A, k);
        for (int j = 0; j < adyacentes.size(); ++j) {
            if(pixelValidoEncendido(adyacentes[i]) && !pertenece(adyacentes[j], obtenidos)){
                tmp.push_back(adyacentes[i]);
            }
        }
    }
}
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
    return (A[p[0]][p[1]] == 1);
}

bool pixelEnRango(const pixel &p, const imagen &A){
    return (p[0] >= 0 && p[0] < A.size() && p[1] >= 0 && p[1] < A[0].size());
}

bool pixelValidoEncendido(const pixel &p, const imagen &A){
    return (pixelEnRango(p, A) && activado(p, A));
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

int apariciones(const pixel &p, const sqPixel &s){
    int contador = 0;

    for (int i = 0; i < s.size(); i++) {
        if (p == s[i]){
            contador++;
        }
    }
    return contador;
}

bool contenida(const sqPixel &sq, const vector<sqPixel> &s){
    bool result = false;
    int contador = 0;

    for (int j = 0; j < s.size() && !result; j++) {
        for (int i = 0; i < sq.size(); i++) {
            if (apariciones(sq[i], sq) == apariciones(sq[i], s[j])){
                contador++;
            }
        }
        result = contador == sq.size();
        contador = 0;
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
    sqPixel obtenidos = {};
    if (pixelValidoEncendido(p,A)){
        obtenidos = {p};
    }
    sqPixel obtenidosAnt = {};
    sqPixel adyacentes = {};
    sqPixel tmp = {};
    sqPixel tmpAnt = {p};
    bool result = false;

    while (!result && obtenidos != obtenidosAnt){
        for (int i = 0; i < tmpAnt.size(); i++) {
            adyacentes = obtenerAdyacentes(tmpAnt[i], A, k);
            for (int j = 0; j < adyacentes.size(); j++) {
                if (pixelValidoEncendido(adyacentes[j], A) && !pertenece(adyacentes[j], obtenidos)){
                    tmp.push_back(adyacentes[j]);
                }
            }
        }
        obtenidosAnt = obtenidos;
        for (int l = 0; l < tmp.size(); l++) {
            obtenidos.push_back(tmp[l]);
        }
        tmpAnt = tmp;
        tmp.clear();
        result = pertenece(q, obtenidos);
    }
    return result;
}

sqPixel obtenerRegion(const imagen &A, const pixel &p, const int &k){
    sqPixel obtenidos = {};
    if (pixelValidoEncendido(p,A)){
        obtenidos = {p};
    }
    sqPixel obtenidosAnt = {};
    sqPixel adyacentes = {};
    sqPixel tmp = {};
    sqPixel tmpAnt = {p};

    while (obtenidos != obtenidosAnt){
        for (int i = 0; i < tmpAnt.size(); i++) {
            adyacentes = obtenerAdyacentes(tmpAnt[i], A, k);
            for (int j = 0; j < adyacentes.size(); j++) {
                if (pixelValidoEncendido(adyacentes[j], A)
                && !pertenece(adyacentes[j], obtenidos) && !pertenece(adyacentes[j], tmp)){
                    tmp.push_back(adyacentes[j]);
                }
            }
        }
        obtenidosAnt = obtenidos;
        for (int l = 0; l < tmp.size(); l++) {
            obtenidos.push_back(tmp[l]);
        }
        tmpAnt = tmp;
        tmp.clear();
    }
    return obtenidos;
}

vector<sqPixel> obtenerTodasLasRegiones(const imagen &A, const int &k){
    vector<sqPixel> regiones = {};
    sqPixel regionActual = {};

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[0].size(); j++) {
            regionActual = obtenerRegion(A, {i,j}, k);
            if (!contenida(regionActual, regiones) && !regionActual.empty()){
                regiones.push_back(regionActual);
            }
        }
    }
    return regiones;
}

float calcularPromedioDeAreas(const imagen &A, const int k){
    float prom = 0.0;
    vector<sqPixel> listaRegiones = obtenerTodasLasRegiones(A, k);
    float sumaPixelesDeRegion = 0.0;
    int sumaRegiones = listaRegiones.size();

    for (int i = 0; i < listaRegiones.size(); i++) {
        sumaPixelesDeRegion += listaRegiones[i].size();
    }

    if (sumaRegiones != 0){
        prom = sumaPixelesDeRegion / sumaRegiones;
    }

    return prom;
}

bool tocaConBackground(const pixel &p, const imagen &A, const int &k){
    sqPixel adyacentes = obtenerAdyacentes(p,A,k);
    bool result = false;

    for (int i = 0; i < adyacentes.size(); i++) {
        if (pixelValidoEncendido(p,A) && pixelEnRango(adyacentes[i],A) && !activado(adyacentes[i],A)){
            result = true;
        }
    }
    return result;
}

bool estaEnBorde(const pixel &p, const imagen &A, const int &k){
    sqPixel adyacentes = obtenerAdyacentes(p,A,k);
    bool result = false;

    for (int i = 0; i < adyacentes.size(); i++) {
        if (pixelValidoEncendido(p,A) && !pixelEnRango(adyacentes[i],A)){
            result = true;
        }
    }
    return result;
}

bool esPixelContorno(const pixel &p, const imagen &A, const int &k){
    return (tocaConBackground(p,A,k) || estaEnBorde(p,A,k));
}

sqPixel estructuranteCentradoEn(const imagen &A, const imagen &B, pixel p){
    vector<pixel> opciones;
    for(int i=0; i<A.size(); i++){
        for(int j=0; j<A[0].size(); j++){
            int n = (B.size()-1)/2;
            if((p[0]-n<=i)&&(i<=p[0]+n)&&(p[1]-n<=j)&&(j<=p[1]+n)){
                opciones.push_back({i,j});
            }
        }
    }
    sqPixel res;
    int n = p[0]-1;
    int m = p[1]-1;
    for(int k=0; k<opciones.size(); k++){
        if(activado({opciones[k][0]-n,opciones[k][1]-m},B)){
            res.push_back(opciones[k]);
        }
    }
    return res;
}

bool esPixelDeDilatacion(const imagen &A, const imagen &B, pixel p){
    sqPixel est = estructuranteCentradoEn(A,B,p);
    bool res = false;
    int i = 0;
    while(i<est.size() && !res){
        if(activado(est[i],A)){
            res = true;
        }
        i++;
    }
    return res;
}

imagen dilatar(const imagen &A, const imagen &B){
    imagen D = A;
    for(int i=0; i < A.size(); i++){
        for(int j=0; j < A[0].size(); j++){
            if(esPixelDeDilatacion(A,B,{i,j})){
                D[i][j] = 1;
            }
        }
    }
    return D;
}

bool esPixelDeErosion(const imagen &A, const imagen &B, const pixel &p){
    sqPixel est = estructuranteCentradoEn(A,B,p);
    bool res = true;
    int i = 0;
    while(i<est.size() && res){
        if(!activado(est[i],A)){
            res = false;
        }
        i++;
    }
    return res;
}

imagen erosionar(const imagen &A, const imagen &B){
    imagen E = A;
    for(int i=0; i<A.size(); i++){
        for(int j= 0; j<A[0].size(); j++){
            if(!esPixelDeErosion(A,B,{i,j})){
                E[i][j] = 0;
            }
        }
    }
    return E;
}

imagen intersecar(const imagen &A, const imagen &B){
    imagen I(A.size(),vector<int>(A[0].size()));
    for(int i=0; i<A.size(); i++){
        for(int j=0; j<A[0].size(); j++){
            if(activado({i,j},A) && activado({i,j},B)){
                I[i][j]=1;
            }
        }
    }
    return I;
}
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




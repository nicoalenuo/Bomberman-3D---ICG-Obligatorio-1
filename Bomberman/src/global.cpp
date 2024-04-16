#include "../lib/global.h"

global* global::instancia = nullptr;

global::global() {
    this->moverArriba = false;
    this->moverAbajo = false;
    this->moverDerecha = false;
    this->moverIzquierda = false;
    this->mouseX = 0;
}

global* global::getInstance() {
    if (instancia == nullptr) {
        instancia = new global();
    }
    return instancia;
}


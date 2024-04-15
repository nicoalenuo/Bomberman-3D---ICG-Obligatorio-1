#include "../lib/global.h"
#include "../lib/bomba.h"

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

void global::insertarBomba(list<bomba*> listBomba, bomba* bomb) {
    float tiempo = bomb->getTiempoBomba();
    auto iter = listBomba.begin();
    while (iter != listBomba.end() && (*iter)->getTiempoBomba() <= bomb->getTiempoBomba()) {
        ++iter;
    }
    listBomba.insert(iter, bomb);
}

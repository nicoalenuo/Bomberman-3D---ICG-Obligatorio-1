#include "../lib/bomberman.h"

bool posicion_valida(posicion pos, tamanio tam) {
    int largoTableroAux = largoTablero * tile_size;
    int anchoTableroAux = anchoTablero * tile_size;

    objeto* obj_1 = estructuras[int(pos.x) / int(tile_size)][int(pos.z) / int(tile_size)];
    objeto* obj_2 = estructuras[int(pos.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];
    objeto* obj_3 = estructuras[int(pos.x + tam.x) / int(tile_size)][int(pos.z) / int(tile_size)];
    objeto* obj_4 = estructuras[int(pos.x + tam.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];

    objeto* obj_5 = bombas[int(pos.x) / int(tile_size)][int(pos.z) / int(tile_size)];
    objeto* obj_6 = bombas[int(pos.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];
    objeto* obj_7 = bombas[int(pos.x + tam.x) / int(tile_size)][int(pos.z) / int(tile_size)];
    objeto* obj_8 = bombas[int(pos.x + tam.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];

    return
        pos.x >= 0 &&
        pos.x + tam.x <= largoTableroAux &&
        pos.z >= 0 &&
        pos.z + tam.z <= anchoTableroAux &&
        (obj_1 == nullptr || pos.x < obj_1->getPosicion().x || pos.x > obj_1->getPosicion().x + obj_1->getTamanio().x || pos.z < obj_1->getPosicion().z || pos.z > obj_1->getPosicion().z + obj_1->getTamanio().z) &&
        (obj_2 == nullptr || pos.x < obj_2->getPosicion().x || pos.x > obj_2->getPosicion().x + obj_2->getTamanio().x || pos.z + tam.z < obj_2->getPosicion().z || pos.z + tam.z > obj_2->getPosicion().z + obj_2->getTamanio().z) &&
        (obj_3 == nullptr || pos.x + tam.x < obj_3->getPosicion().x || pos.x + tam.x > obj_3->getPosicion().x + obj_3->getTamanio().x || pos.z < obj_3->getPosicion().z || pos.z > obj_3->getPosicion().z + obj_3->getTamanio().z) &&
        (obj_4 == nullptr || pos.x + tam.x < obj_4->getPosicion().x || pos.x + tam.x > obj_4->getPosicion().x + obj_4->getTamanio().x || pos.z + tam.z < obj_4->getPosicion().z || pos.z + tam.z > obj_4->getPosicion().z + obj_4->getTamanio().z) &&
        (obj_5 == nullptr || pos.x < obj_5->getPosicion().x || pos.x > obj_5->getPosicion().x + obj_5->getTamanio().x || pos.z < obj_5->getPosicion().z || pos.z > obj_5->getPosicion().z + obj_5->getTamanio().z) &&
        (obj_6 == nullptr || pos.x < obj_6->getPosicion().x || pos.x > obj_6->getPosicion().x + obj_6->getTamanio().x || pos.z + tam.z < obj_6->getPosicion().z || pos.z + tam.z > obj_6->getPosicion().z + obj_6->getTamanio().z) &&
        (obj_7 == nullptr || pos.x + tam.x < obj_7->getPosicion().x || pos.x + tam.x > obj_7->getPosicion().x + obj_7->getTamanio().x || pos.z < obj_7->getPosicion().z || pos.z > obj_7->getPosicion().z + obj_7->getTamanio().z) &&
        (obj_8 == nullptr || pos.x + tam.x < obj_8->getPosicion().x || pos.x + tam.x > obj_8->getPosicion().x + obj_8->getTamanio().x || pos.z + tam.z < obj_8->getPosicion().z || pos.z + tam.z > obj_8->getPosicion().z + obj_8->getTamanio().z);
}


bomberman::bomberman(posicion pos, tamanio tam, GLfloat velocidad) : personaje(pos, tam, velocidad) {
    this->vida = 1;
    this->moverBomba = false;
    this->largoBomba = 1;
    this->tiempoBomba = 1.0; //Para poner algo pongo 1, falta probar y ajustar mediante la parte grafica
    this->maxBomba = 1;
    this->cantActual = 0;

    tie(player_commands, player_data) = ControladorObjetos::load_obj("objs/Chicken02.obj", 1);
}

void bomberman::actualizar() {

    if (moverArriba) {
        if (mouseX >= 45 && mouseX < 135)
            if (posicion_valida({ pos.x - velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad;
        if (mouseX >= 135 && mouseX < 225)
            if (posicion_valida({ pos.x, 0, pos.z + velocidad }, { tam.x, 0,tam.z }))
                pos.z += velocidad;
        if (mouseX >= 225 && mouseX < 315) 
            if (posicion_valida({ pos.x + velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad;
        if (mouseX >= 315 || mouseX < 45)
            if (posicion_valida({ pos.x, 0,pos.z - velocidad }, { tam.x, 0,tam.z }))
                pos.z -= velocidad;
    }
    if (moverAbajo) {
        if (mouseX >= 45 && mouseX < 135)
            if (posicion_valida({ pos.x + velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad;
        if (mouseX >= 135 && mouseX < 225)
            if (posicion_valida({ pos.x, 0, pos.z - velocidad }, { tam.x, 0, tam.z }))
                pos.z -= velocidad;
        if (mouseX >= 225 && mouseX < 315)
            if (posicion_valida({ pos.x - velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad;
        if (mouseX >= 315 || mouseX < 45)
            if (posicion_valida({ pos.x, 0, pos.z + velocidad }, { tam.x, 0, tam.z }))
                pos.z += velocidad;
    }

    if (moverDerecha) {
        if (mouseX >= 45 && mouseX < 135)
            if (posicion_valida({ pos.x, 0, pos.z - velocidad }, { tam.x, 0, tam.z }))
                pos.z -= velocidad;
        if (mouseX >= 135 && mouseX < 225)
            if (posicion_valida({ pos.x - velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad;
        if (mouseX >= 225 && mouseX < 315)
            if (posicion_valida({ pos.x, 0, pos.z + velocidad }, { tam.x, 0, tam.z }))
                pos.z += velocidad;
        if (mouseX >= 315 || mouseX < 45)
            if (posicion_valida({ pos.x + velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad;
    }

    if (moverIzquierda) {
        if (mouseX >= 45 && mouseX < 135)
            if (posicion_valida({ pos.x, 0, pos.z + velocidad }, { tam.x, 0, tam.z }))
                pos.z += velocidad;
        if (mouseX >= 135 && mouseX < 225)
            if (posicion_valida({ pos.x + velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad;
        if (mouseX >= 225 && mouseX < 315)
            if (posicion_valida({ pos.x, 0, pos.z - velocidad }, { tam.x, 0, tam.z }))
                pos.z -= velocidad;
        if (mouseX >= 315 || mouseX < 45)
            if (posicion_valida({ pos.x - velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad;
    }
}

void bomberman::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    ControladorObjetos::DrawMultiplePoints(GL_QUADS, player_commands, player_data, ControladorTexturas::getTextura(PLAYER));
    glPopMatrix();
}


int bomberman::getVida() {
    return this->vida;
}

void bomberman::setVida(int vida) {
    this->vida = vida;
}

int bomberman::getMaxBomba() {
    return this->maxBomba;
}

void bomberman::setMaxBomba(int max) {
    this->maxBomba = max;
}

int bomberman::getCantBomba() {
    return this->cantActual;
}

void bomberman::setCantBomba(int cant) {
    this->cantActual = cant;
}

void bomberman::aumentarCantBomba() {
    this->cantActual += 1;
}

void bomberman::disminuirCantBomba() {
    this->cantActual -= 1;
}

bool bomberman::getMoverBomba() {
    return this->moverBomba;
}

void bomberman::setMoverBomba(bool mov) {
    this->moverBomba = mov;
}

float bomberman::getTiempoBomba() {
    return this->tiempoBomba;
}

void bomberman::setTiempoBomba(float tiempo) {
    this->tiempoBomba = tiempo;
}

int bomberman::getLargoBomba() {
    return this->largoBomba;
}

void bomberman::setLargoBomba(int largo) {
    this->largoBomba = largo;
}

float bomberman::getVelocidad() {
    return this->velocidad;
}

void bomberman::setVelocidad(float vel) {
    this->velocidad = vel;
}

bool bomberman::bombaDisponible() {
    return (this->maxBomba > this->cantActual);
}
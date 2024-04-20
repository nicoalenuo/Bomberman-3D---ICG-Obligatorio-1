#include "../lib/bomberman.h"
#include "../lib/controlador.h"

bomberman::bomberman(posicion pos, tamanio tam) : personaje(pos, tam, GLfloat(0.1)) {
    this->vida = 1;
    this->moverBomba = false;
    this->largoBomba = 1;
    this->tiempoBomba = 1.0; //Para poner algo pongo 1, falta probar y ajustar mediante la parte grafica
    this->maxBomba = 1;
    this->cantActual = 0;

    tie(player_commands, player_data) = ControladorObjetos::load_obj("objs/Chicken02.obj", 1);
}

void bomberman::actualizar() {
    Controlador* controlador = Controlador::getInstance();
    int mouseX = (*global).mouseX;

    if ((*global).moverArriba) {
        if (mouseX >= 45 && mouseX < 135)
            if ((*controlador).posicion_valida({ pos.x - velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad;
        if (mouseX >= 135 && mouseX < 225)
            if ((*controlador).posicion_valida({ pos.x, 0, pos.z + velocidad }, { tam.x, 0,tam.z }))
                pos.z += velocidad;
        if (mouseX >= 225 && mouseX < 315) 
            if ((*controlador).posicion_valida({ pos.x + velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad;
        if (mouseX >= 315 || mouseX < 45)
            if ((*controlador).posicion_valida({ pos.x, 0,pos.z - velocidad }, { tam.x, 0,tam.z }))
                pos.z -= velocidad;
    }
    if ((*global).moverAbajo) {
        if (mouseX >= 45 && mouseX < 135)
            if ((*controlador).posicion_valida({ pos.x + velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad;
        if (mouseX >= 135 && mouseX < 225)
            if ((*controlador).posicion_valida({ pos.x, 0, pos.z - velocidad }, { tam.x, 0, tam.z }))
                pos.z -= velocidad;
        if (mouseX >= 225 && mouseX < 315)
            if ((*controlador).posicion_valida({ pos.x - velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad;
        if (mouseX >= 315 || mouseX < 45)
            if ((*controlador).posicion_valida({ pos.x, 0, pos.z + velocidad }, { tam.x, 0, tam.z }))
                pos.z += velocidad;
    }

    if ((*global).moverDerecha) {
        if (mouseX >= 45 && mouseX < 135)
            if ((*controlador).posicion_valida({ pos.x, 0, pos.z - velocidad }, { tam.x, 0, tam.z }))
                pos.z -= velocidad;
        if (mouseX >= 135 && mouseX < 225)
            if ((*controlador).posicion_valida({ pos.x - velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad;
        if (mouseX >= 225 && mouseX < 315)
            if ((*controlador).posicion_valida({ pos.x, 0, pos.z + velocidad }, { tam.x, 0, tam.z }))
                pos.z += velocidad;
        if (mouseX >= 315 || mouseX < 45)
            if ((*controlador).posicion_valida({ pos.x + velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad;
    }

    if ((*global).moverIzquierda) {
        if (mouseX >= 45 && mouseX < 135)
            if ((*controlador).posicion_valida({ pos.x, 0, pos.z + velocidad }, { tam.x, 0, tam.z }))
                pos.z += velocidad;
        if (mouseX >= 135 && mouseX < 225)
            if ((*controlador).posicion_valida({ pos.x + velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad;
        if (mouseX >= 225 && mouseX < 315)
            if ((*controlador).posicion_valida({ pos.x, 0, pos.z - velocidad }, { tam.x, 0, tam.z }))
                pos.z -= velocidad;
        if (mouseX >= 315 || mouseX < 45)
            if ((*controlador).posicion_valida({ pos.x - velocidad, 0, pos.z }, { tam.x, 0, tam.z }))
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
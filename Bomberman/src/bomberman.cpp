#include "../lib/bomberman.h"
#include "../lib/controlador.h"

bomberman::bomberman(GLfloat x, GLfloat z, GLfloat anchoX, GLfloat anchoZ, GLfloat alt): personaje(x,z, anchoX, anchoZ, alt, GLfloat(0.1)) {
    this->vida = 1;
    this->moverBomba = false;
    this->largoBomba = 1;
    this->tiempoBomba = 1.0; //Para poner algo pongo 1, falta probar y ajustar mediante la parte grafica
    this->maxBomba = 1;
    this->cantActual = 0;
}

bool bomberman::posicion_valida(GLfloat coord_x, GLfloat coord_z, GLfloat ancho_x, GLfloat ancho_z, int largoTablero, int anchoTablero, objeto*** tablero) {
    return 
        coord_x >= 0 &&
        coord_x + ancho_x <= largoTablero &&
        coord_z >= 0 &&
        coord_z + ancho_z <= anchoTablero &&
        dynamic_cast<estructura*>(tablero[int(coord_x) / int(global->tile_size)][int(coord_z) / int(global->tile_size)]) == nullptr &&
        dynamic_cast<estructura*>(tablero[int(coord_x) / int(global->tile_size)][int(coord_z + ancho_z) / int(global->tile_size)]) == nullptr &&
        dynamic_cast<estructura*>(tablero[int(coord_x + ancho_x) / int(global->tile_size)][int(coord_z) / int(global->tile_size)]) == nullptr &&
        dynamic_cast<estructura*>(tablero[int(coord_x + ancho_x) / int(global->tile_size)][int(coord_z + ancho_z) / int(global->tile_size)]) == nullptr;
}

void bomberman::actualizar() {
    Controlador* controlador = Controlador::getInstance();
    objeto*** tablero = (*controlador).getTablero();
    int largoTablero = controlador->getLargoTablero() * global->tile_size;
    int anchoTablero = controlador->getAnchoTablero() * global->tile_size;
    int mouseX = (*global).mouseX;

    if ((*global).moverArriba) {
        if (mouseX >= 45 && mouseX < 135)
            if (posicion_valida(coord_x - velocidad, coord_z, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_x -= velocidad;
        if (mouseX >= 135 && mouseX < 225)
            if (posicion_valida(coord_x, coord_z + velocidad, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_z += velocidad;
        if (mouseX >= 225 && mouseX < 315) 
            if (posicion_valida(coord_x + velocidad, coord_z, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_x += velocidad;
        if (mouseX >= 315 || mouseX < 45)
            if (posicion_valida(coord_x, coord_z - velocidad, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_z -= velocidad;
    }
    if ((*global).moverAbajo) {
        if (mouseX >= 45 && mouseX < 135)
            if (posicion_valida(coord_x + velocidad, coord_z, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_x += velocidad;
        if (mouseX >= 135 && mouseX < 225)
            if (posicion_valida(coord_x, coord_z - velocidad, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_z -= velocidad;
        if (mouseX >= 225 && mouseX < 315)
            if (posicion_valida(coord_x - velocidad, coord_z, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_x -= velocidad;
        if (mouseX >= 315 || mouseX < 45)
            if (posicion_valida(coord_x, coord_z + velocidad, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_z += velocidad;
    }

    if ((*global).moverDerecha) {
        if (mouseX >= 45 && mouseX < 135)
            if (posicion_valida(coord_x, coord_z - velocidad, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_z -= velocidad;
        if (mouseX >= 135 && mouseX < 225)
            if (posicion_valida(coord_x - velocidad, coord_z, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_x -= velocidad;
        if (mouseX >= 225 && mouseX < 315)
            if (posicion_valida(coord_x, coord_z + velocidad, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_z += velocidad;
        if (mouseX >= 315 || mouseX < 45)
            if (posicion_valida(coord_x + velocidad, coord_z, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_x += velocidad;
    }

    if ((*global).moverIzquierda) {
        if (mouseX >= 45 && mouseX < 135)
            if (posicion_valida(coord_x, coord_z + velocidad, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_z += velocidad;
        if (mouseX >= 135 && mouseX < 225)
            if (posicion_valida(coord_x + velocidad, coord_z, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_x += velocidad;
        if (mouseX >= 225 && mouseX < 315)
            if (posicion_valida(coord_x, coord_z - velocidad, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_z -= velocidad;
        if (mouseX >= 315 || mouseX < 45)
            if (posicion_valida(coord_x - velocidad, coord_z, ancho_x, ancho_z, largoTablero, anchoTablero, tablero))
                coord_x -= velocidad;
    }
}

void bomberman::dibujar() {
    glBegin(GL_QUADS);

    // Cara de abajo
    glColor3f(1.0f, 0.0f, 0.0f); // Rojo
    glVertex3f(coord_x, 0, coord_z);
    glVertex3f(coord_x + ancho_x, 0, coord_z);
    glVertex3f(coord_x + ancho_x, 0, coord_z + ancho_z);
    glVertex3f(coord_x, 0, coord_z + ancho_z);

    // Cara de arriba
    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    glVertex3f(coord_x, altura, coord_z);
    glVertex3f(coord_x + ancho_x, altura, coord_z);
    glVertex3f(coord_x + ancho_x, altura, coord_z + ancho_z);
    glVertex3f(coord_x, altura, coord_z + ancho_z);

    // Cara de atras
    glColor3f(0.0f, 0.0f, 1.0f); // Azul
    glVertex3f(coord_x, 0, coord_z);
    glVertex3f(coord_x + ancho_x, 0, coord_z );
    glVertex3f(coord_x + ancho_x, altura, coord_z);
    glVertex3f(coord_x, altura, coord_z);

    // Cara de adelante
    glColor3f(1.0f, 1.0f, 0.0f); // Amarillo
    glVertex3f(coord_x, 0, coord_z + ancho_z);
    glVertex3f(coord_x + ancho_x, 0, coord_z + ancho_z);
    glVertex3f(coord_x + ancho_x, altura, coord_z + ancho_z);
    glVertex3f(coord_x, altura, coord_z + ancho_z);

    // Cara izquierda
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glVertex3f(coord_x, 0, coord_z );
    glVertex3f(coord_x, 0, coord_z + ancho_z);
    glVertex3f(coord_x, altura, coord_z + ancho_z);
    glVertex3f(coord_x, altura, coord_z );

    // Cara derecha (x = 1)
    glColor3f(0.0f, 1.0f, 1.0f); // Cian
    glVertex3f(coord_x + ancho_x, 0, coord_z);
    glVertex3f(coord_x + ancho_x, 0, coord_z + ancho_z);
    glVertex3f(coord_x + ancho_x, altura, coord_z + ancho_z);
    glVertex3f(coord_x + ancho_x, altura, coord_z);
    glEnd();
    
}


int bomberman::getVida() {
    return this->vida;
}

void bomberman::setVida(int vid) {
    this->vida = vid;
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
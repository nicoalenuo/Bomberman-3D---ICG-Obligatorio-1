#include "../lib/bomberman.h"

bomberman::bomberman(GLfloat x, GLfloat z): personaje(x,z) {
    this->vida = 1;
    this->moverBomba = false;
    this->largoBomba = 1;
    this->velocidad = 1; //Para poner algo pongo 1, falta probar y ajustar mediante la parte grafica
    this->tiempoBomba = 1; //Para poner algo pongo 1, falta probar y ajustar mediante la parte grafica
    this->maxBomba = 1;
}

void bomberman::actualizar() {
    int mouseX = (*global).getMouseX();

    if ((*global).getMoverArriba()) {
        if (mouseX >= 45 && mouseX < 135)
            coord_x -= 0.3;
        if (mouseX >= 135 && mouseX < 225)
            coord_z += 0.3;
        if (mouseX >= 225 && mouseX < 315)
            coord_x += 0.3;
        if (mouseX >= 315 || mouseX < 45)
            coord_z -= 0.3;
    }
    if ((*global).getMoverAbajo()) {
        if (mouseX >= 45 && mouseX < 135)
            coord_x += 0.3;
        if (mouseX >= 135 && mouseX < 225)
            coord_z -= 0.3;
        if (mouseX >= 225 && mouseX < 315)
            coord_x -= 0.3;
        if (mouseX >= 315 || mouseX < 45)
            coord_z += 0.3;
    }

    if ((*global).getMoverDerecha()) {
        if (mouseX >= 45 && mouseX < 135)
            coord_z -= 0.3;
        if (mouseX >= 135 && mouseX < 225)
            coord_x -= 0.3;
        if (mouseX >= 225 && mouseX < 315)
            coord_z += 0.3;
        if (mouseX >= 315 || mouseX < 45)
            coord_x += 0.3;
    }

    if ((*global).getMoverIzquierda()) {
        if (mouseX >= 45 && mouseX < 135)
            coord_z += 0.3;
        if (mouseX >= 135 && mouseX < 225)
            coord_x += 0.3;
        if (mouseX >= 225 && mouseX < 315)
            coord_z -= 0.3;
        if (mouseX >= 315 || mouseX < 45)
            coord_x -= 0.3;
    }
}

void bomberman::dibujar() {
    GLfloat angleRadians = (*global).getMouseX() * (3.14159f / 180.0f);
    GLfloat camX = coord_x + 20.0f * sin(angleRadians);
    GLfloat camZ = coord_z + 20.0f * cos(angleRadians);

    gluLookAt(camX, 30, camZ, coord_x, 0, coord_z, 0, 1, 0);

    glBegin(GL_QUADS);
    // Cara frontal (z = 1/2)
    glColor3f(1.0f, 0.0f, 0.0f); // Rojo
    glVertex3f(-1 + coord_x, 0, 1 + coord_z);
    glVertex3f(1 + coord_x, 0, 1 + coord_z);
    glVertex3f(1 + coord_x, 1, 1 + coord_z);
    glVertex3f(-1 + coord_x, 1, 1 + coord_z);

    // Cara posterior (z = -1/2)
    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    glVertex3f(-1 + coord_x, 0, -1 + coord_z);
    glVertex3f(1 + coord_x, 0, -1 + coord_z);
    glVertex3f(1 + coord_x, 1, -1 + coord_z);
    glVertex3f(-1 + coord_x, 1, -1 + coord_z);

    // Cara superior (y = 1/2)
    glColor3f(0.0f, 0.0f, 1.0f); // Azul
    glVertex3f(-1 + coord_x, 1, -1 + coord_z);
    glVertex3f(1 + coord_x, 1, -1 + coord_z);
    glVertex3f(1 + coord_x, 1, 1 + coord_z);
    glVertex3f(-1 + coord_x, 1, 1 + coord_z);

    // Cara inferior (y = -1/2)
    glColor3f(1.0f, 1.0f, 0.0f); // Amarillo
    glVertex3f(-1 + coord_x, 0, -1 + coord_z);
    glVertex3f(1 + coord_x, 0, -1 + coord_z);
    glVertex3f(1 + coord_x, 0, 1 + coord_z);
    glVertex3f(-1 + coord_x, 0, 1 + coord_z);

    // Cara izquierda (x = -1/2)
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glVertex3f(-1 + coord_x, 0, -1 + coord_z);
    glVertex3f(-1 + coord_x, 0, 1 + coord_z);
    glVertex3f(-1 + coord_x, 1, 1 + coord_z);
    glVertex3f(-1 + coord_x, 1, -1 + coord_z);

    // Cara derecha (x = 1/2)
    glColor3f(0.0f, 1.0f, 1.0f); // Cian
    glVertex3f(1 + coord_x, 0, -1 + coord_z);
    glVertex3f(1 + coord_x, 0, 1 + coord_z);
    glVertex3f(1 + coord_x, 1, 1 + coord_z);
    glVertex3f(1 + coord_x, 1, -1 + coord_z);
    glEnd();
}


int bomberman::getVida() {
    return this->vida;
}

void bomberman::setVida(int vid) {
    this->vida = vid;
}

list<bomba*> bomberman::getBomba() {
    return this->bombas;
}

void bomberman::setBomba(list<bomba*> bomb) {
    this->bombas = bomb;
}

int bomberman::getMaxBomba() {
    return this->maxBomba;
}

void bomberman::setMaxBomba(int max) {
    this->maxBomba = max;
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
    return (this->maxBomba > 0 && (this->maxBomba == this->bombas.size()));
}

// el bomberman manda una solicitud de que quiere poner una bomba, ya el controlador se encargará si puede o no
// las coordenadas las va a sacar la clase de la parte grafica mediante el controlador? o un controlador (nuevo) para grafico? (como? A)
void bomberman::ponerBomba(int x, int z) {
}
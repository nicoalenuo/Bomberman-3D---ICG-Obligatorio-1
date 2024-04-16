#include "../lib/bomberman.h"

bomberman::bomberman(GLfloat x, GLfloat z): personaje(x,z) {
    this->vida = 1;
    this->moverBomba = false;
    this->largoBomba = 1;
    this->tiempoBomba = 1; //Para poner algo pongo 1, falta probar y ajustar mediante la parte grafica
    this->maxBomba = 1;
    velocidad = GLfloat(0.3);
}

void bomberman::actualizar() {
    int mouseX = (*global).mouseX;

    if ((*global).moverArriba) {
        if (mouseX >= 45 && mouseX < 135)
            coord_x -= velocidad;
        if (mouseX >= 135 && mouseX < 225)
            coord_z += velocidad;
        if (mouseX >= 225 && mouseX < 315)
            coord_x += velocidad;
        if (mouseX >= 315 || mouseX < 45)
            coord_z -= velocidad;
    }
    if ((*global).moverAbajo) {
        if (mouseX >= 45 && mouseX < 135)
            coord_x += velocidad;
        if (mouseX >= 135 && mouseX < 225)
            coord_z -= velocidad;
        if (mouseX >= 225 && mouseX < 315)
            coord_x -= velocidad;
        if (mouseX >= 315 || mouseX < 45)
            coord_z += velocidad;
    }

    if ((*global).moverDerecha) {
        if (mouseX >= 45 && mouseX < 135)
            coord_z -= velocidad;
        if (mouseX >= 135 && mouseX < 225)
            coord_x -= velocidad;
        if (mouseX >= 225 && mouseX < 315)
            coord_z += velocidad;
        if (mouseX >= 315 || mouseX < 45)
            coord_x += velocidad;
    }

    if ((*global).moverIzquierda) {
        if (mouseX >= 45 && mouseX < 135)
            coord_z += velocidad;
        if (mouseX >= 135 && mouseX < 225)
            coord_x += velocidad;
        if (mouseX >= 225 && mouseX < 315)
            coord_z -= velocidad;
        if (mouseX >= 315 || mouseX < 45)
            coord_x -= velocidad;
    }
}

void bomberman::dibujar() {
    GLfloat angleRadians = (*global).mouseX * (3.14159f / 180.0f);

    GLfloat desplazamiento = global->largoEstructura / 2; // para que quede centrado

    GLfloat xReal = (coord_x - 14.5) * global->largoEstructura + desplazamiento/2;
    GLfloat zReal = (coord_z - 5.5) * global->largoEstructura + desplazamiento/2;

    GLfloat camX = xReal + 20.0f * sin(angleRadians);
    GLfloat camZ = zReal + 20.0f * cos(angleRadians);

    gluLookAt(camX, 30, camZ, xReal, 0, zReal, 0, 1, 0);
    glBegin(GL_QUADS);
    // Cara frontal (z = 1)
    glColor3f(1.0f, 0.0f, 0.0f); // Rojo
    glVertex3f(xReal, 0, zReal + desplazamiento);
    glVertex3f(xReal + desplazamiento, 0, zReal + desplazamiento);
    glVertex3f(xReal + desplazamiento, 2, zReal + desplazamiento);
    glVertex3f(xReal, 2, zReal + desplazamiento);

    // Cara posterior (z = -1)
    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    glVertex3f(xReal, 0, zReal );
    glVertex3f(xReal + desplazamiento, 0, zReal );
    glVertex3f(xReal + desplazamiento, 2, zReal );
    glVertex3f(xReal, 2, zReal );

    // Cara superior (y = 1)
    glColor3f(0.0f, 0.0f, 1.0f); // Azul
    glVertex3f(xReal, 2, zReal );
    glVertex3f(xReal + desplazamiento, 2, zReal );
    glVertex3f(xReal + desplazamiento, 2, zReal + desplazamiento);
    glVertex3f(xReal, 2, zReal + desplazamiento);

    // Cara inferior (y = 0)
    glColor3f(1.0f, 1.0f, 0.0f); // Amarillo
    glVertex3f(xReal, 0, zReal );
    glVertex3f(xReal + desplazamiento, 0, zReal );
    glVertex3f(xReal + desplazamiento, 0, zReal + desplazamiento);
    glVertex3f(xReal, 0, zReal + desplazamiento);

    // Cara izquierda (x = -1)
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glVertex3f(xReal, 0, zReal );
    glVertex3f(xReal, 0, zReal + desplazamiento);
    glVertex3f(xReal, 2, zReal + desplazamiento);
    glVertex3f(xReal, 2, zReal );

    // Cara derecha (x = 1)
    glColor3f(0.0f, 1.0f, 1.0f); // Cian
    glVertex3f(xReal + desplazamiento, 0, zReal );
    glVertex3f(xReal + desplazamiento, 0, zReal + desplazamiento);
    glVertex3f(xReal + desplazamiento, 2, zReal + desplazamiento);
    glVertex3f(xReal + desplazamiento, 2, zReal );
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

// el bomberman manda una solicitud de que quiere poner una bomba, ya el controlador se encargar� si puede o no
// las coordenadas las va a sacar la clase de la parte grafica mediante el controlador? o un controlador (nuevo) para grafico? (como? A)
void bomberman::ponerBomba(int x, int z) {
}
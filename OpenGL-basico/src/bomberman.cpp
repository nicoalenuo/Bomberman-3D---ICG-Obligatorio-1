#include "../lib/bomberman.h"

bomberman::bomberman(int x, int z) {
	this->coord_x = (float)x;
	this->coord_z = (float)z;
	this->maxBomba = 1;

    global = global::getInstance();
}

void bomberman::actualizar() {
    if ((*global).moverArriba) {
        if ((*global).mouseX >= 45 && (*global).mouseX < 135)
            coord_x -= this->velocidad;
        if ((*global).mouseX >= 135 && (*global).mouseX < 225)
            coord_z += this->velocidad;
        if ((*global).mouseX >= 225 && (*global).mouseX < 315)
            coord_x += this->velocidad;
        if ((*global).mouseX >= 315 || (*global).mouseX < 45)
            coord_z -= this->velocidad;
    }
    if ((*global).moverAbajo) {
        if ((*global).mouseX >= 45 && (*global).mouseX < 135)
            coord_x += this->velocidad;
        if ((*global).mouseX >= 135 && (*global).mouseX < 225)
            coord_z -= this->velocidad;
        if ((*global).mouseX >= 225 && (*global).mouseX < 315)
            coord_x -= this->velocidad;
        if ((*global).mouseX >= 315 || (*global).mouseX < 45)
            coord_z += this->velocidad;
    }

    if ((*global).moverDerecha) {
        if ((*global).mouseX >= 45 && (*global).mouseX < 135)
            coord_z -= this->velocidad;
        if ((*global).mouseX >= 135 && (*global).mouseX < 225)
            coord_x -= this->velocidad;
        if ((*global).mouseX >= 225 && (*global).mouseX < 315)
            coord_z += this->velocidad;
        if ((*global).mouseX >= 315 || (*global).mouseX < 45)
            coord_x += this->velocidad;
    }

    if ((*global).moverIzquierda) {
        if ((*global).mouseX >= 45 && (*global).mouseX < 135)
            coord_z += this->velocidad;
        if ((*global).mouseX >= 135 && (*global).mouseX < 225)
            coord_x += this->velocidad;
        if ((*global).mouseX >= 225 && (*global).mouseX < 315)
            coord_z -= this->velocidad;
        if ((*global).mouseX >= 315 || (*global).mouseX < 45)
            coord_x -= this->velocidad;
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
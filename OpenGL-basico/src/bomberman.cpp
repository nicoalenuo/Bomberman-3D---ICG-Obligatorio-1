#include "../lib/bomberman.h"

bomberman::bomberman(int x, int z) {
	this->coord_x = (float)x;
	this->coord_z = (float)z;
	this->maxBomba = 1;

    global = global::getInstance();
}

void bomberman::actualizar() {
    if ((*global).getMoverArriba()) {
        if ((*global).getMouseX() >= 45 && (*global).getMouseX() < 135)
            coord_x -= 0.3;
        if ((*global).getMouseX() >= 135 && (*global).getMouseX() < 225)
            coord_z += 0.3;
        if ((*global).getMouseX() >= 225 && (*global).getMouseX() < 315)
            coord_x += 0.3;
        if ((*global).getMouseX() >= 315 || (*global).getMouseX() < 45)
            coord_z -= 0.3;
    }
    if ((*global).getMoverAbajo()) {
        if ((*global).getMouseX() >= 45 && (*global).getMouseX() < 135)
            coord_x += 0.3;
        if ((*global).getMouseX() >= 135 && (*global).getMouseX() < 225)
            coord_z -= 0.3;
        if ((*global).getMouseX() >= 225 && (*global).getMouseX() < 315)
            coord_x -= 0.3;
        if ((*global).getMouseX() >= 315 || (*global).getMouseX() < 45)
            coord_z += 0.3;
    }

    if ((*global).getMoverDerecha()) {
        if ((*global).getMouseX() >= 45 && (*global).getMouseX() < 135)
            coord_z -= 0.3;
        if ((*global).getMouseX() >= 135 && (*global).getMouseX() < 225)
            coord_x -= 0.3;
        if ((*global).getMouseX() >= 225 && (*global).getMouseX() < 315)
            coord_z += 0.3;
        if ((*global).getMouseX() >= 315 || (*global).getMouseX() < 45)
            coord_x += 0.3;
    }

    if ((*global).getMoverIzquierda()) {
        if ((*global).getMouseX() >= 45 && (*global).getMouseX() < 135)
            coord_z += 0.3;
        if ((*global).getMouseX() >= 135 && (*global).getMouseX() < 225)
            coord_x += 0.3;
        if ((*global).getMouseX() >= 225 && (*global).getMouseX() < 315)
            coord_z -= 0.3;
        if ((*global).getMouseX() >= 315 || (*global).getMouseX() < 45)
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
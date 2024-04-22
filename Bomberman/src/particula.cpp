#include "../lib/particula.h"

particula::particula(posicion pos, tamanio tam, aceleracion ac, velocidad vel) : objeto(pos, tam) {
    tiempoParticula = 0;
    this->ac = ac;
    this->vel = vel;
}
GLfloat tiempoSegundos;

void particula::actualizar() {
    tiempoSegundos = GLfloat(tiempoParticula) / 1000.0f;
    pos.x = pos.x + vel.x;
    pos.y = ac.y * tiempoSegundos * tiempoSegundos + vel.y * tiempoSegundos + 3.0f;
    pos.z = pos.z + vel.z;
    tiempoParticula += frameDelay;
}

void particula::dibujar() {
    glPushMatrix();

    glTranslatef(pos.x, pos.y, pos.z);
    glBegin(GL_QUADS);

    glColor3f(1.0, 1.0, 1.0);

    glVertex3f(-tam.x, 0, -tam.z);
    glVertex3f(tam.x, 0, -tam.z);
    glVertex3f(tam.x, 0, tam.z);
    glVertex3f(-tam.x, 0, tam.z);

    // Cara de arriba
    glVertex3f(-tam.x, tam.y, -tam.z);
    glVertex3f(tam.x, tam.y, -tam.z);
    glVertex3f(tam.x, tam.y, tam.z);
    glVertex3f(-tam.x, tam.y, tam.z);

    // Cara de atras
    glVertex3f(-tam.x, 0, -tam.z);
    glVertex3f(tam.x, 0, -tam.z);
    glVertex3f(tam.x, tam.y, -tam.z);
    glVertex3f(-tam.x, tam.y, -tam.z);

    // Cara de adelante
    glVertex3f(-tam.x, 0, tam.z);
    glVertex3f(tam.x, 0, tam.z);
    glVertex3f(tam.x, tam.y, tam.z);
    glVertex3f(-tam.x, tam.y, tam.z);

    // Cara izquierda
    glVertex3f(-tam.x, 0, -tam.z);
    glVertex3f(-tam.x, 0, tam.z);
    glVertex3f(-tam.x, tam.y, tam.z);
    glVertex3f(-tam.x, tam.y, -tam.z);

    // Cara derecha
    glVertex3f(tam.x, 0, -tam.z);
    glVertex3f(tam.x, 0, tam.z);
    glVertex3f(tam.x, tam.y, tam.z);
    glVertex3f(tam.x, tam.y, -tam.z);
    glEnd();
    glPopMatrix();
}
#include "../lib/estructura.h"

estructura::estructura(posicion pos, tamanio tam, bool dest) : objeto(pos, tam) {
	this->destructible = dest;
}

bool estructura::getDestructible() {
	return this->destructible;
}

void estructura::setDestructible(bool dest) {
	this->destructible = dest;
}

void estructura::actualizar() {
}

void estructura::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ControladorTexturas::getTextura(destructible ? ESTRUCTURA_DESTRUCTIBLE : ESTRUCTURA_NO_DESTRUCTIBLE));

    glBegin(GL_QUADS);

    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);
    glTexCoord2f(0, 1);
    glVertex3f(tam.x, 0, 0);
    glTexCoord2f(1, 1);
    glVertex3f(tam.x, 0, tam.z);
    glTexCoord2f(1, 0);
    glVertex3f(0, 0, tam.z);

    // Cara de arriba
    glTexCoord2f(0, 0);
    glVertex3f(0, tam.y, 0);
    glTexCoord2f(0, 1);
    glVertex3f(tam.x, tam.y, 0);
    glTexCoord2f(1, 1);
    glVertex3f(tam.x, tam.y, tam.z);
    glTexCoord2f(1, 0);
    glVertex3f(0, tam.y, tam.z);

    // Cara de atras
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);
    glTexCoord2f(0, 1);
    glVertex3f(tam.x, 0, 0);
    glTexCoord2f(1, 1);
    glVertex3f(tam.x, tam.y, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0, tam.y, 0);

    // Cara de adelante
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, tam.z);
    glTexCoord2f(0, 1);
    glVertex3f(tam.x, 0, tam.z);
    glTexCoord2f(1, 1);
    glVertex3f(tam.x, tam.y, tam.z);
    glTexCoord2f(1, 0);
    glVertex3f(0, tam.y, tam.z);

    // Cara izquierda
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0, 0, tam.z);
    glTexCoord2f(1, 1);
    glVertex3f(0, tam.y, tam.z);
    glTexCoord2f(1, 0);
    glVertex3f(0, tam.y, 0);

    // Cara derecha (x = 1)
    glTexCoord2f(0, 0);
    glVertex3f(tam.x, 0, 0);
    glTexCoord2f(0, 1);
    glVertex3f(tam.x, 0, tam.z);
    glTexCoord2f(1, 1);
    glVertex3f(tam.x, tam.y, tam.z);
    glTexCoord2f(1, 0);
    glVertex3f(tam.x, tam.y, 0);
    glEnd();
    glPopMatrix();
}

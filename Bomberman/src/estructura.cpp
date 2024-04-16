#include "../lib/estructura.h"

estructura::estructura(GLfloat x, GLfloat z, GLfloat anchoX, GLfloat anchoZ, GLfloat alt, bool dest) : objeto(x, z, anchoX, anchoZ, alt) {
	this->destructible = dest;
	this->powerUp = nullptr;
}

bool estructura::getDestructible() {
	return this->destructible;
}

void estructura::setDestructible(bool dest) {
	this->destructible = dest;
}

bonificador* estructura::getPowerUp() {
	return this->powerUp;
}

void estructura::setPowerUp(bonificador* power) {
	this->powerUp = power;
}

void estructura::actualizar() {
	if (this->destructible) {
		//si es destructible entonces hace cosas en actualizar
	}
}

void estructura::dibujar() {
    glBindTexture(GL_TEXTURE_2D, ControladorTexturas::getTextura(destructible ? ESTRUCTURA_DESTRUCTIBLE : ESTRUCTURA_NO_DESTRUCTIBLE));

    glBegin(GL_QUADS);

    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0, 0);
    glVertex3f(coord_x, 0, coord_z);
    glTexCoord2f(0, 1);
    glVertex3f(coord_x + ancho_x, 0, coord_z);
    glTexCoord2f(1, 1);
    glVertex3f(coord_x + ancho_x, 0, coord_z + ancho_z);
    glTexCoord2f(1, 0);
    glVertex3f(coord_x, 0, coord_z + ancho_z);

    // Cara de arriba
    glTexCoord2f(0, 0);
    glVertex3f(coord_x, altura, coord_z);
    glTexCoord2f(0, 1);
    glVertex3f(coord_x + ancho_x, altura, coord_z);
    glTexCoord2f(1, 1);
    glVertex3f(coord_x + ancho_x, altura, coord_z + ancho_z);
    glTexCoord2f(1, 0);
    glVertex3f(coord_x, altura, coord_z + ancho_z);

    // Cara de atras
    glTexCoord2f(0, 0);
    glVertex3f(coord_x, 0, coord_z);
    glTexCoord2f(0, 1);
    glVertex3f(coord_x + ancho_x, 0, coord_z);
    glTexCoord2f(1, 1);
    glVertex3f(coord_x + ancho_x, altura, coord_z);
    glTexCoord2f(1, 0);
    glVertex3f(coord_x, altura, coord_z);

    // Cara de adelante
    glTexCoord2f(0, 0);
    glVertex3f(coord_x, 0, coord_z + ancho_z);
    glTexCoord2f(0, 1);
    glVertex3f(coord_x + ancho_x, 0, coord_z + ancho_z);
    glTexCoord2f(1, 1);
    glVertex3f(coord_x + ancho_x, altura, coord_z + ancho_z);
    glTexCoord2f(1, 0);
    glVertex3f(coord_x, altura, coord_z + ancho_z);

    // Cara izquierda
    glTexCoord2f(0, 0);
    glVertex3f(coord_x, 0, coord_z);
    glTexCoord2f(0, 1);
    glVertex3f(coord_x, 0, coord_z + ancho_z);
    glTexCoord2f(1, 1);
    glVertex3f(coord_x, altura, coord_z + ancho_z);
    glTexCoord2f(1, 0);
    glVertex3f(coord_x, altura, coord_z);

    // Cara derecha (x = 1)
    glTexCoord2f(0, 0);
    glVertex3f(coord_x + ancho_x, 0, coord_z);
    glTexCoord2f(0, 1);
    glVertex3f(coord_x + ancho_x, 0, coord_z + ancho_z);
    glTexCoord2f(1, 1);
    glVertex3f(coord_x + ancho_x, altura, coord_z + ancho_z);
    glTexCoord2f(1, 0);
    glVertex3f(coord_x + ancho_x, altura, coord_z);
    glEnd();
}

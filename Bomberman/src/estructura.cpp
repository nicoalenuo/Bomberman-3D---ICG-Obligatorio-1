#include "../lib/estructura.h"

estructura::estructura(vector_3 pos, vector_3 tam, bool dest) : objeto(pos, tam) {
	this->destructible = dest;
}

void estructura::actualizar() {
}

void estructura::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);

    if (texturas_habilitadas)
        glBindTexture(GL_TEXTURE_2D, ControladorTexturas::getTextura(destructible ? ESTRUCTURA_DESTRUCTIBLE : ESTRUCTURA_NO_DESTRUCTIBLE));

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);

    //Cara de abajo
    glTexCoord2f(0, 0);
    glVertex3f(-tam.x, 0, -tam.z);

    glTexCoord2f(0, 1);
    glVertex3f(tam.x, 0, -tam.z);

    glTexCoord2f(1, 1);
    glVertex3f(tam.x, 0, tam.z);

    glTexCoord2f(1, 0);
    glVertex3f(-tam.x, 0, tam.z);

    // Cara de arriba
    glTexCoord2f(0, 0);
    glVertex3f(-tam.x, tam.y, -tam.z);

    glTexCoord2f(0, 1);
    glVertex3f(tam.x, tam.y, -tam.z);

    glTexCoord2f(1, 1);
    glVertex3f(tam.x, tam.y, tam.z);

    glTexCoord2f(1, 0);
    glVertex3f(-tam.x, tam.y, tam.z);

    // Cara de atras
    glTexCoord2f(0, 0);
    glVertex3f(-tam.x, 0, -tam.z);

    glTexCoord2f(0, 1);
    glVertex3f(tam.x, 0, -tam.z);

    glTexCoord2f(1, 1);
    glVertex3f(tam.x, tam.y, -tam.z);

    glTexCoord2f(1, 0);
    glVertex3f(-tam.x, tam.y, -tam.z);

    // Cara de adelante
    glTexCoord2f(0, 0);
    glVertex3f(-tam.x, 0, tam.z);

    glTexCoord2f(0, 1);
    glVertex3f(tam.x, 0, tam.z);

    glTexCoord2f(1, 1);
    glVertex3f(tam.x, tam.y, tam.z);

    glTexCoord2f(1, 0);
    glVertex3f(-tam.x, tam.y, tam.z);

    // Cara izquierda
    glTexCoord2f(0, 0);
    glVertex3f(-tam.x, 0, -tam.z);

    glTexCoord2f(0, 1);
    glVertex3f(-tam.x, 0, tam.z);

    glTexCoord2f(1, 1);
    glVertex3f(-tam.x, tam.y, tam.z);

    glTexCoord2f(1, 0);
    glVertex3f(-tam.x, tam.y, -tam.z);

    // Cara derecha (x = 1)
    glTexCoord2f(0, 0);
    glVertex3f(tam.x, 0, -tam.z);

    glTexCoord2f(0, 1);
    glVertex3f(tam.x, 0, tam.z);

    glTexCoord2f(1, 1);
    glVertex3f(tam.x, tam.y, tam.z);

    glTexCoord2f(1, 0);
    glVertex3f(tam.x, tam.y, -tam.z);

    glEnd();
    glPopMatrix();
}
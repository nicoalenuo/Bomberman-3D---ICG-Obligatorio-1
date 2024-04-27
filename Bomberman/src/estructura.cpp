#include "../lib/estructura.h"

estructura::estructura(vector_3 pos, vector_3 tam, bool dest) : objeto(pos, tam) {
	this->destructible = dest;
}

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(-0.3, 0.3);
estructura::~estructura() {
    for (int j = 0; j < 150; j++) {
        particulas.push_back(
            new particula(
                { pos.x, pos.y + (tile_size / 2), pos.z },
                { GLfloat(0.07), GLfloat(0.07), GLfloat(0.07) },
                { 0, -25, 0 },
                { GLfloat(dis(gen)), 10, GLfloat(dis(gen)) },
                ControladorTexturas::getTextura(ESTRUCTURA_DESTRUCTIBLE),
                PARTICULA_ESTRUCTURA_DESTRUCTIBLE
            )
        );
    }
}

void estructura::actualizar() {
}

void estructura::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);

    if (texturas_habilitadas) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ControladorTexturas::getTextura(destructible ? ESTRUCTURA_DESTRUCTIBLE : ESTRUCTURA_NO_DESTRUCTIBLE));
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    glBegin(GL_QUADS);

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

    // Cara derecha 
    glTexCoord2f(0, 0);
    glVertex3f(tam.x, 0, -tam.z);

    glTexCoord2f(0, 1);
    glVertex3f(tam.x, 0, tam.z);

    glTexCoord2f(1, 1);
    glVertex3f(tam.x, tam.y, tam.z);

    glTexCoord2f(1, 0);
    glVertex3f(tam.x, tam.y, -tam.z);

    glEnd();

    if (texturas_habilitadas)
        glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
}
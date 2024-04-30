#include "../lib/door.h"

door::door(vector_3 pos, vector_3 tam) : objeto(pos, tam) {
    this->abierta = true;//Hay que inicializar en falso y setear en true cuando no existan enemigos
    this->visible = false;
}

bool door::getAbierta() {
    return this->abierta;
}

void door::setAbierta(bool abierta) {
    this->abierta = abierta;
}

bool door::getVisible() {
    return this->visible;
}

void door::setVisible(bool visible) {
    this->visible = visible;
}

bool door::intersecta(bomberman* b) {
    return pos.x < b->getPosicion().x + b->getTamanio().x &&
           pos.x + tam.x > b->getPosicion().x &&
           pos.z < b->getPosicion().z + b->getTamanio().z &&
           pos.z + tam.z > b->getPosicion().z;
}

void door::actualizar() {
    int x = getIndiceTablero(pos.x);
    int z = getIndiceTablero(pos.z);

    if (estructuras[x][z] == nullptr) {
        visible = true;
    }
}

void door::dibujar() {
    if (this->visible) {
        glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);

        if (texturas_habilitadas) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, ControladorTexturas::getTextura(TEXTURA_PUERTA));
        }
        glColor3f(1.0, 0.f, 1.0);

        glBegin(GL_QUADS);

        //Cara de abajo
        glTexCoord2f(0.5, 0.5);
        glVertex3f(-tam.x, 0, -tam.z);

        glTexCoord2f(0.5, 1);
        glVertex3f(tam.x, 0, -tam.z);

        glTexCoord2f(1, 1);
        glVertex3f(tam.x, 0, tam.z);

        glTexCoord2f(1, 0.5);
        glVertex3f(-tam.x, 0, tam.z);

        // Cara de arriba
        glTexCoord2f(0.5, 0.5);
        glVertex3f(-tam.x, tam.y, -tam.z);

        glTexCoord2f(0.5, 1);
        glVertex3f(tam.x, tam.y, -tam.z);

        glTexCoord2f(1, 1);
        glVertex3f(tam.x, tam.y, tam.z);

        glTexCoord2f(1, 0.5);
        glVertex3f(-tam.x, tam.y, tam.z);

        // Cara de atras
        glTexCoord2f(1, 0);
        glVertex3f(-tam.x, 0, -tam.z);

        glTexCoord2f(0.5, 0);
        glVertex3f(tam.x, 0, -tam.z);

        glTexCoord2f(0.5, 0.5);
        glVertex3f(tam.x, tam.y, -tam.z);

        glTexCoord2f(1, 0.5);
        glVertex3f(-tam.x, tam.y, -tam.z);

        // Cara de adelante
        glTexCoord2f(0.5, 0);
        glVertex3f(-tam.x, 0, tam.z);

        glTexCoord2f(0, 0);
        glVertex3f(tam.x, 0, tam.z);

        glTexCoord2f(0, 0.5);
        glVertex3f(tam.x, tam.y, tam.z);

        glTexCoord2f(0.5, 0.5);
        glVertex3f(-tam.x, tam.y, tam.z);

        // Cara izquierda
        glTexCoord2f(0.5, 0);
        glVertex3f(-tam.x, 0, -tam.z);

        glTexCoord2f(0, 0);
        glVertex3f(-tam.x, 0, tam.z);

        glTexCoord2f(0, 0.5);
        glVertex3f(-tam.x, tam.y, tam.z);

        glTexCoord2f(0.5, 0.5);
        glVertex3f(-tam.x, tam.y, -tam.z);

        // Cara derecha (x = 1)
        glTexCoord2f(0.5, 0);
        glVertex3f(tam.x, 0, -tam.z);

        glTexCoord2f(0, 0);
        glVertex3f(tam.x, 0, tam.z);

        glTexCoord2f(0, 0.5);
        glVertex3f(tam.x, tam.y, tam.z);

        glTexCoord2f(0.5, 0.5);
        glVertex3f(tam.x, tam.y, -tam.z);

        glEnd();

        if (texturas_habilitadas) 
            glDisable(GL_TEXTURE_2D);

        glPopMatrix();
    }
}
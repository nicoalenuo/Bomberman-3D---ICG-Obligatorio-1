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
           pos.y < b->getPosicion().y + b->getTamanio().y &&
           pos.y + tam.y > b->getPosicion().y;
}

void door::actualizar() {
    int x = getPosicionXEnTablero(pos.x, tam.x);
    int z = getPosicionZEnTablero(pos.z, tam.z);

    if (estructuras[x][z] == nullptr) {
        visible = true;
    }
}

void door::dibujar() {
    if (this->visible) {
        glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);

        if (texturas_habilitadas)
            glBindTexture(GL_TEXTURE_2D, ControladorTexturas::getTextura(TEXTURA_PUERTA));

        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);

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
        glPopMatrix();
    }
}
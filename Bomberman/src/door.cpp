#include "../lib/door.h"

door::door(vector_3 pos, vector_3 tam) : objeto(pos, tam) {
    this->visible = false;
}

bool door::intersecta(bomberman* b) {
    return pos.x < b->getPosicion().x + b->getTamanio().x &&
           pos.x + tam.x > b->getPosicion().x &&
           pos.z < b->getPosicion().z + b->getTamanio().z &&
           pos.z + tam.z > b->getPosicion().z;
}

void door::actualizar() {
    if (!visible && estructuras[getIndiceTablero(pos.x)][getIndiceTablero(pos.z)] == nullptr)
        visible = true;
}

void door::dibujar() {
    if (this->visible) {
        glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);
        GLfloat color[3] = { 0.31f, 0.0f, 7.72f };
        ControladorObjetos::dibujarCubo(tam, ControladorTexturas::getTextura(TEXTURA_PUERTA), color);
        glPopMatrix();
    }
}
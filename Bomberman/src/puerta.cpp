#include "../lib/puerta.h"

puerta::puerta(vector_3 pos, vector_3 tam) : objeto(pos, tam) {
    this->visible = false;
}

bool puerta::intersecta(bomberman* b) {
    return pos.x < b->getPosicion().x + b->getTamanio().x &&
           pos.x + tam.x > b->getPosicion().x &&
           pos.z < b->getPosicion().z + b->getTamanio().z &&
           pos.z + tam.z > b->getPosicion().z;
}

void puerta::actualizar() {
    if (!visible && estructuras[getIndiceTablero(pos.x)][getIndiceTablero(pos.z)] == nullptr)
        visible = true;
}

void puerta::dibujar() {
    if (this->visible) {
        glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);
        GLfloat color[3] = { 0.31f, 0.0f, 7.72f };
        ControladorObjetos::getInstance()->dibujarCubo(tam, ControladorTexturas::getInstance()->getTextura(TEXTURA_PUERTA), color);
        glPopMatrix();
    }
}
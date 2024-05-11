#include "../lib/estructura.h"

estructura::estructura(vector_3 pos, vector_3 tam, bool dest) : objeto(pos, tam) {
	this->destructible = dest;
}

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(-0.3, 0.3);
estructura::~estructura() {
    int posX = getIndiceTablero(pos.x);
    int posZ = getIndiceTablero(pos.z);
    if (destructible) {
        estructuras[posX][posZ] = nullptr;
        sumarPuntaje(10);
        for (int j = 0; j < 150; j++) {
            particulas.push_back(
                new particula_estructura(
                    { pos.x, pos.y + (tile_size / 2), pos.z },
                    { GLfloat(0.07), GLfloat(0.07), GLfloat(0.07) },
                    { 0, -25, 0 },
                    { GLfloat(dis(gen)), 10, GLfloat(dis(gen)) },
                    ControladorTexturas::getInstance()->getTextura(ESTRUCTURA_DESTRUCTIBLE)
                )
            );
        }
    }
}

void estructura::actualizar() {
}

void estructura::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    GLfloat color[3];
    if (destructible) {
        color[0] = 144.f / 255;
        color[1] = 12.f / 255;
        color[2] = 63.f / 255;
    } else {
        color[0] = 175.f / 255;
        color[1] = 175.f / 255;
        color[2] = 175.f / 255;
    }
    ControladorObjetos::getInstance()->dibujarCubo(tam, ControladorTexturas::getInstance()->getTextura(destructible ? ESTRUCTURA_DESTRUCTIBLE : ESTRUCTURA_NO_DESTRUCTIBLE), color);
    glPopMatrix();
}
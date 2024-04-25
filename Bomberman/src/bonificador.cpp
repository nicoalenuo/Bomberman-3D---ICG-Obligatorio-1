#include "../lib/bonificador.h"

random_device rdBonificador;
mt19937 genBonificador(rdBonificador());
uniform_real_distribution<> disBonificador(0.0, 1.0); 
bonificador::bonificador(vector_3 pos, vector_3 tam, tipo_poder tipo_p) : objeto(pos, tam) {
    if (tipo == BONIFICADOR_RANDOM) {
        double random_num = disBonificador(genBonificador);
        if (random_num < 0.25f)
            tipo = AUMENTAR_ALCANCE_BOMBAS;
        else if (random_num < 0.5f)
            tipo = INMORTALIDAD;
        else if (random_num < 0.75f)
            tipo = AUMENTAR_VELOCIDAD;
        else
            tipo = BOMBAS_ATRAVIESAN_ESTRUCTURAS;
    }
    else {
        tipo = tipo_p;
    }
    subiendo = true;
}

void bonificador::actualizar() {
    if (subiendo) {
        pos.y += 0.03f;
        if (pos.y > tile_size)
            subiendo = false;
    }
    else {
        pos.y -= 0.03f;
        if (pos.y < tile_size / 2)
            subiendo = true;
    }
}

void bonificador::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);

    //Cara de abajo
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
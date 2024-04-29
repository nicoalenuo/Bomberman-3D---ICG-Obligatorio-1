#include "../lib/bonificador.h"

random_device rdBonificador;
mt19937 genBonificador(rdBonificador());
uniform_real_distribution<> disBonificador(0.0, 1.0); 
bonificador::bonificador(vector_3 pos, vector_3 tam, tipo_poder tipo_p) : objeto(pos, tam) {
    //tremenda función me acabo de hacer, y que paseo que te acabo de meter ;)
    //que manera de robar codigo de internet ahre
    if (tipo == BONIFICADOR_RANDOM) {
        double intervalo = 1.0 / ((static_cast<int>(tipo_poder::BONIFICADOR_RANDOM)) - 1);
        int aux = 0;
        double random_num = disBonificador(genBonificador);
        while (random_num > intervalo) {
            random_num -= intervalo;
            aux++;
        }
        tipo = static_cast<tipo_poder>(aux);
    }
    else {
        tipo = tipo_p;
    }

    subiendo = true;
    visible = false;
    angulo = 0;
}

void bonificador::actualizar() { //falta rotarlo
    glLoadIdentity();
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

    if (estructuras[getIndiceTablero(pos.x)][getIndiceTablero(pos.z)] == nullptr) 
        visible = true;
}

void bonificador::dibujar() {
    if (visible) { //se asume que si no es nullptr, es una estructura destructible por como se crea
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
}

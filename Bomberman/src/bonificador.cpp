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
    rotacion_y = 0;
}


random_device rdParticulaBonificador;
mt19937 genParticulaBonificador(rdParticulaBonificador());
uniform_real_distribution<> disParticulaBonificador(-tile_size / 2, tile_size / 2);
uniform_real_distribution<> disParticulaBonificadorVelocidad(-0.01, 0.01);
void bonificador::actualizar() { 
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

    rotacion_y += 4;
    rotacion_y %= 360;


    if (!visible && estructuras[getIndiceTablero(pos.x)][getIndiceTablero(pos.z)] == nullptr) 
        visible = true;

    if (visible) {
        particulas.push_back(
            new particula_bonificador(
                { GLfloat(pos.x + disParticulaBonificador(genParticulaBonificador)), 0.0f, GLfloat(pos.z + disParticulaBonificador(genParticulaBonificador)) },
                { GLfloat(0.025), GLfloat(0.025), GLfloat(0.025) },
                { 0.0f, 1.0f, 0.0f },
                { GLfloat(disParticulaBonificadorVelocidad(genParticulaBonificador)), 0, GLfloat(disParticulaBonificadorVelocidad(genParticulaBonificador)) }
            )
        );
    }

    if (visible &&
        jugador->getPosicion().x + jugador->getTamanio().x > pos.x + tam.x && 
        jugador->getPosicion().x - jugador->getTamanio().x < pos.x - tam.x &&
        jugador->getPosicion().z + jugador->getTamanio().z > pos.z + tam.z &&
        jugador->getPosicion().z - jugador->getTamanio().x < pos.z - tam.z) {
            int x = getIndiceTablero(pos.x);
            int z = getIndiceTablero(pos.z);
            bonificadores[x][z] = nullptr;
            ControladorPoderes::activarPoder(tipo, 30000); //30 segundos
            delete this;
    }
}

void bonificador::dibujar() {
    if (visible) { //se asume que si no es nullptr, es una estructura destructible por como se crea
        glPushMatrix();

        glTranslatef(pos.x, pos.y, pos.z);
        glRotatef(rotacion_y, 0, 1, 0);

        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);

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

#include "../lib/bonificador.h"

random_device rdBonificador;
mt19937 genBonificador(rdBonificador());
uniform_real_distribution<> disBonificador(0.0, 1.0); 
bonificador::bonificador(vector_3 pos, vector_3 tam, tipo_poder tipo_p) : objeto(pos, tam) {
    //tremenda funci�n me acabo de hacer, y que paseo que te acabo de meter ;)
    //que manera de robar codigo de internet ahre
    if (tipo_p == BONIFICADOR_RANDOM) {
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
    tiempo_entre_particulas = 0;
}

random_device rdParticulaBonificador;
mt19937 genParticulaBonificador(rdParticulaBonificador());
uniform_real_distribution<> disParticulaBonificador(-tile_size / 2, tile_size / 2);
uniform_real_distribution<> disParticulaBonificadorVelocidad(-0.01, 0.01);
void bonificador::actualizar() { 
    if (!visible && estructuras[getIndiceTablero(pos.x)][getIndiceTablero(pos.z)] == nullptr) 
        visible = true;

    if (visible) {
        tiempo_entre_particulas += int(elapsed_time);

        if (subiendo) {
            pos.y += 0.03f * (elapsed_time / frameDelay);
            if (pos.y > tile_size)
                subiendo = false;
        }
        else {
            pos.y -= 0.03f * (elapsed_time / frameDelay);
            if (pos.y < tile_size / 2)
                subiendo = true;
        }

        rotacion_y += 4 * (elapsed_time / frameDelay);
        rotacion_y = GLfloat(fmod(rotacion_y, 360));

        GLfloat colorLuz[4] = { 1.0f, 1.0f, 0.0f, 0.1f };
        ControladorLuz::getInstance()->pedirLuz(pos, colorLuz);

        if (tiempo_entre_particulas > 30) {
            particulas.push_back(
                new particula_bonificador(
                    { GLfloat(pos.x + disParticulaBonificador(genParticulaBonificador)), 0.0f, GLfloat(pos.z + disParticulaBonificador(genParticulaBonificador)) },
                    { GLfloat(0.025), GLfloat(0.025), GLfloat(0.025) },
                    { 0.0f, 0.5f, 0.0f },
                    { GLfloat(disParticulaBonificadorVelocidad(genParticulaBonificador)), 0, GLfloat(disParticulaBonificadorVelocidad(genParticulaBonificador)) }
                )
            );
            tiempo_entre_particulas = 0;
        }
    }

    if (visible &&
        jugador->getPosicion().x + jugador->getTamanio().x > pos.x + tam.x && 
        jugador->getPosicion().x - jugador->getTamanio().x < pos.x - tam.x &&
        jugador->getPosicion().z + jugador->getTamanio().z > pos.z + tam.z &&
        jugador->getPosicion().z - jugador->getTamanio().x < pos.z - tam.z) {
            int x = getIndiceTablero(pos.x);
            int z = getIndiceTablero(pos.z);
            bonificadores[x][z] = nullptr;
            sumarPuntaje(500);
            ControladorPoderes::getInstance()->activarPoder(tipo, ControladorPoderes::getInstance()->poderDependeDeTiempo(tipo) ? 10000 : 1);
            ControladorAudio::getInstance()->playAudio(sonido::bonificacion);
            delete this;
    }
}

GLfloat colorBonificador[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
void bonificador::dibujar() {
    if (visible) {
        glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);
        glRotatef(rotacion_y, 0, 1, 0);
        ControladorObjetos::getInstance()->dibujarCubo(tam, 0, colorBonificador);
        glPopMatrix();
    }
}

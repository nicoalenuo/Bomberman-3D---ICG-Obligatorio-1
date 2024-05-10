#include "../lib/enemigo.h"

enemigo::enemigo(vector_3 pos, vector_3 tam, bool orientacionX, color_enemigo color) : personaje(pos, tam, GLfloat(0.1)) {
    this->orientacionX = orientacionX;
    if (orientacionX) {
        moverX = true;
        moverNX = false;
        moverZ = false;
        moverNZ = false;
    } else {
        moverX = false;
        moverNX = false;
        moverZ = true;
        moverNZ = false;
    }
    
    eliminar = false;

    probCambiarPos = 0.3;
    rotacion_y_actual = 0;
    rotacion_z_actual = 0;
    balanceandoseDerecha = false;

    this->color = color;
}

bool enemigo::getOrientacionX() {
    return orientacionX;
}

void enemigo::setOrientacionX(bool orientacionX) {
    this->orientacionX = orientacionX;
    if (orientacionX) {
        moverX = true;
        moverNX = false;
        moverZ = false;
        moverNZ = false;
    } else {
        moverX = false;
        moverNX = false;
        moverZ = true;
        moverNZ = false;
    }
}

bool enemigo::intersecta(bomberman* b) {
    return pos.x < b->getPosicion().x + b->getTamanio().x &&
        pos.x + tam.x > b->getPosicion().x &&
        pos.z < b->getPosicion().z + b->getTamanio().z &&
        pos.z + tam.z > b->getPosicion().z;
}

bool centroConMovimiento(vector_3 pos) {
    return abs(round(pos.x) - (pos.x)) < 0.01 &&
           abs(round(pos.z) - (pos.z)) < 0.01 &&
           int(round(pos.x)) % 2 == 1 &&
           int(round(pos.z)) % 2 == 1;
}

bool posicion_valida_parcial(vector_3 pos, bool orientacionX) {
    int largoTableroAux = largoTablero * int(tile_size);
    int anchoTableroAux = anchoTablero * int(tile_size);

    int x,z,p,n;
    x = getIndiceTablero(pos.x);
    z = getIndiceTablero(pos.z);

    objeto *obj_1, *obj_2, *obj_3, *obj_4 = nullptr;

    if (orientacionX) {
        p = min(x + 1, largoTablero-1);
        n = max(x - 1, 0);
        obj_1 = estructuras[p][z];
        obj_2 = estructuras[n][z];
        obj_3 = bombas[p][z];
        obj_4 = bombas[n][z];
    } else {
        p = min(z + 1, anchoTablero-1);
        n = max(z - 1, 0);
        obj_1 = estructuras[x][p];
        obj_2 = estructuras[x][n];
        obj_3 = bombas[x][p];
        obj_4 = bombas[x][n];
    }

    return
        (obj_1 == nullptr && obj_3 == nullptr) ||
        (obj_2 == nullptr && obj_4 == nullptr);
}


void enemigo::actualizar() {
    bool cambio = false;
    //probablemente deba cambiar de lugar
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    GLfloat desplazamiento = velocidad * (elapsed_time / frameDelay);

    if (orientacionX) {
        if (centroConMovimiento(pos) && (dis(gen) < probCambiarPos) && posicion_valida_parcial(pos, false)) {
            moverX = false;
            moverNX = false;
            moverZ = dis(gen) < probCambiarPos;
            moverNZ = !moverZ;
            orientacionX = false;
            cambio = true;
        }
        if (moverX) {
            if (posicion_valida({ pos.x + desplazamiento, 0, pos.z }, { tam.x, 0, tam.z })) {
                pos.x += desplazamiento;
                rotacion_y_actual = 0;
            } else {
                moverX = false;
                moverNX = true;
                rotacion_y_actual = 180;
            }
        }
        if (moverNX) {
            if (posicion_valida({ pos.x - desplazamiento, 0, pos.z }, { tam.x, 0, tam.z })) {
                pos.x -= desplazamiento;
                rotacion_y_actual = 180;
            } else {
                moverX = true;
                moverNX = false;
                rotacion_y_actual = 0;
            }
        }
    }
    if (!orientacionX) {
        if (!cambio && centroConMovimiento(pos) && (dis(gen) < probCambiarPos) && posicion_valida_parcial(pos, true)) {
            moverX = dis(gen) < probCambiarPos;
            moverNX = !moverX;
            moverZ = false;
            moverNZ = false;
            orientacionX = true;
        }
        if (moverZ) {
            if (posicion_valida({ pos.x, 0, pos.z + desplazamiento }, { tam.x, 0, tam.z })) {
                pos.z += desplazamiento;
                rotacion_y_actual = 270;
            }
            else {
                moverZ = false;
                moverNZ = true;
                rotacion_y_actual = 90;
            }
        }
        if (moverNZ) {
            if (posicion_valida({ pos.x, 0, pos.z - desplazamiento }, { tam.x, 0, tam.z })) {
                pos.z -= desplazamiento;
                rotacion_y_actual = 90;
            }
            else {
                moverZ = true;
                moverNZ = false;
                rotacion_y_actual = 270;
            }
        }
    }

    if (balanceandoseDerecha) {
        rotacion_z_actual += GLfloat(2 * (elapsed_time / frameDelay));
        if (rotacion_z_actual > 8) {
            balanceandoseDerecha = false;
        }
    }
    else {
        rotacion_z_actual -= 2 * (elapsed_time / frameDelay);
        if (rotacion_z_actual < -8) {
            balanceandoseDerecha = true;
        }
    }

    if (contactoConFuego()) {
        sumarPuntaje(100);
        eliminar = true;
    }

}

void enemigo::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    //glRotatef(rotacion_z_actual, 0, 0, 1); //falta ajustar para que nj
    glRotatef(rotacion_y_actual, 0, 1, 0);
    switch (color) {
        case ROJO:
            ControladorObjetos::getInstance()->dibujar(OBJ_ENEMY_ROJO);
            break;
        case AZUL:
            ControladorObjetos::getInstance()->dibujar(OBJ_ENEMY_AZUL);
            break;
        case VERDE:
            ControladorObjetos::getInstance()->dibujar(OBJ_ENEMY_VERDE);
            break;
    }
   
    glPopMatrix();
}
#include "../lib/bomberman.h"

bool posicion_valida(vector_3 pos, vector_3 tam) {
    int largoTableroAux = largoTablero * int(tile_size);
    int anchoTableroAux = anchoTablero * int(tile_size);

    objeto* obj_1 = estructuras[int(pos.x - tam.x) / int(tile_size)][int(pos.z - tam.z) / int(tile_size)];
    objeto* obj_2 = estructuras[int(pos.x - tam.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];
    objeto* obj_3 = estructuras[int(pos.x + tam.x) / int(tile_size)][int(pos.z - tam.z) / int(tile_size)];
    objeto* obj_4 = estructuras[int(pos.x + tam.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];

    objeto* obj_5 = bombas[int(pos.x - tam.x) / int(tile_size)][int(pos.z - tam.z) / int(tile_size)];
    objeto* obj_6 = bombas[int(pos.x - tam.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];
    objeto* obj_7 = bombas[int(pos.x + tam.x) / int(tile_size)][int(pos.z - tam.z) / int(tile_size)];
    objeto* obj_8 = bombas[int(pos.x + tam.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];

    return
        pos.x - tam.x >= 0 &&
        pos.x + tam.x < largoTableroAux &&
        pos.z - tam.z >= 0 &&
        pos.z + tam.z < anchoTableroAux &&
        (obj_1 == nullptr || pos.x - tam.x < obj_1->getPosicion().x - obj_1->getTamanio().x || pos.x - tam.x > obj_1->getPosicion().x + obj_1->getTamanio().x || pos.z - tam.z < obj_1->getPosicion().z - obj_1->getTamanio().z || pos.z - tam.z > obj_1->getPosicion().z + obj_1->getTamanio().z) &&
        (obj_2 == nullptr || pos.x - tam.x < obj_2->getPosicion().x - obj_2->getTamanio().x || pos.x - tam.x > obj_2->getPosicion().x + obj_2->getTamanio().x || pos.z + tam.z < obj_2->getPosicion().z - obj_2->getTamanio().z || pos.z + tam.z > obj_2->getPosicion().z + obj_2->getTamanio().z) &&
        (obj_3 == nullptr || pos.x + tam.x < obj_3->getPosicion().x - obj_3->getTamanio().x || pos.x + tam.x > obj_3->getPosicion().x + obj_3->getTamanio().x || pos.z - tam.z < obj_3->getPosicion().z - obj_3->getTamanio().z || pos.z - tam.z > obj_3->getPosicion().z + obj_3->getTamanio().z) &&
        (obj_4 == nullptr || pos.x + tam.x < obj_4->getPosicion().x - obj_4->getTamanio().x || pos.x + tam.x > obj_4->getPosicion().x + obj_4->getTamanio().x || pos.z + tam.z < obj_4->getPosicion().z - obj_4->getTamanio().z || pos.z + tam.z > obj_4->getPosicion().z + obj_4->getTamanio().z) &&
        (obj_5 == nullptr || pos.x - tam.x < obj_5->getPosicion().x - obj_5->getTamanio().x || pos.x - tam.x > obj_5->getPosicion().x + obj_5->getTamanio().x || pos.z - tam.z < obj_5->getPosicion().z - obj_5->getTamanio().z || pos.z - tam.z > obj_5->getPosicion().z + obj_5->getTamanio().z) &&
        (obj_6 == nullptr || pos.x - tam.x < obj_6->getPosicion().x - obj_6->getTamanio().x || pos.x - tam.x > obj_6->getPosicion().x + obj_6->getTamanio().x || pos.z + tam.z < obj_6->getPosicion().z - obj_6->getTamanio().z || pos.z + tam.z > obj_6->getPosicion().z + obj_6->getTamanio().z) &&
        (obj_7 == nullptr || pos.x + tam.x < obj_7->getPosicion().x - obj_7->getTamanio().x || pos.x + tam.x > obj_7->getPosicion().x + obj_7->getTamanio().x || pos.z - tam.z < obj_7->getPosicion().z - obj_7->getTamanio().z || pos.z - tam.z > obj_7->getPosicion().z + obj_7->getTamanio().z) &&
        (obj_8 == nullptr || pos.x + tam.x < obj_8->getPosicion().x - obj_8->getTamanio().x || pos.x + tam.x > obj_8->getPosicion().x + obj_8->getTamanio().x || pos.z + tam.z < obj_8->getPosicion().z - obj_8->getTamanio().z || pos.z + tam.z > obj_8->getPosicion().z + obj_8->getTamanio().z);
}


bomberman::bomberman(vector_3 pos, vector_3 tam, GLfloat velocidad) : personaje(pos, tam, velocidad) {
    vida = 1;
    moverBomba = false;
    largoBomba = 2;
    tiempoBomba = 2000;
    maxBomba = 1;
    cantActual = 0;
    rotacion_y_actual = 0;
    rotacion_z_actual = 0;
    balanceandoseDerecha = false;
}

int rotacionY, rotacionZ;
void bomberman::actualizar() {
    if (moverArriba) {
        if (mouseX >= 45 && mouseX < 135) {
            rotacionY = 90;
            if (posicion_valida({ pos.x - velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad * velocidad_juego;
        }
        else if (mouseX >= 135 && mouseX < 225) {
            rotacionY = 180;
            if (posicion_valida({ pos.x, 0, pos.z + velocidad * velocidad_juego }, { tam.x, 0,tam.z }))
                pos.z += velocidad * velocidad_juego;
        }
        else if (mouseX >= 225 && mouseX < 315) {
            rotacionY = 270;
            if (posicion_valida({ pos.x + velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad * velocidad_juego;
        }
        else {
            rotacionY = 0;
            if (posicion_valida({ pos.x, 0,pos.z - velocidad * velocidad_juego }, { tam.x, 0,tam.z }))
                pos.z -= velocidad * velocidad_juego;
        }
    }
    if (moverAbajo) {
        if (mouseX >= 45 && mouseX < 135) {
            rotacionY = 270;
            if (posicion_valida({ pos.x + velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad * velocidad_juego;
        }
        else if (mouseX >= 135 && mouseX < 225) {
            rotacionY = 0;
            if (posicion_valida({ pos.x, 0, pos.z - velocidad * velocidad_juego }, { tam.x, 0, tam.z }))
                pos.z -= velocidad * velocidad_juego;
        }
        else if (mouseX >= 225 && mouseX < 315) {
            rotacionY = 90;
            if (posicion_valida({ pos.x - velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad * velocidad_juego;
        }
        else {
            rotacionY = 180;
            if (posicion_valida({ pos.x, 0, pos.z + velocidad * velocidad_juego }, { tam.x, 0, tam.z }))
                pos.z += velocidad * velocidad_juego;
        }
    }

    if (moverDerecha) {
        if (mouseX >= 45 && mouseX < 135) {
            rotacionY = 0;
            if (posicion_valida({ pos.x, 0, pos.z - velocidad * velocidad_juego }, { tam.x, 0, tam.z }))
                pos.z -= velocidad * velocidad_juego;
        }
        else if (mouseX >= 135 && mouseX < 225) {
            rotacionY = 90;
            if (posicion_valida({ pos.x - velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad * velocidad_juego;
        }
        else if (mouseX >= 225 && mouseX < 315) {
            rotacionY = 180;
            if (posicion_valida({ pos.x, 0, pos.z + velocidad * velocidad_juego }, { tam.x, 0, tam.z }))
                pos.z += velocidad * velocidad_juego;
        }
        else {
            rotacionY = 270;
            if (posicion_valida({ pos.x + velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad * velocidad_juego;
        }
    }

    if (moverIzquierda) {
        if (mouseX >= 45 && mouseX < 135) {
            rotacionY = 180;
            if (posicion_valida({ pos.x, 0, pos.z + velocidad * velocidad_juego }, { tam.x, 0, tam.z }))
                pos.z += velocidad * velocidad_juego;
        }
        else if (mouseX >= 135 && mouseX < 225) {
            rotacionY = 270;
            if (posicion_valida({ pos.x + velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad * velocidad_juego;
        }
        else if (mouseX >= 225 && mouseX < 315) {
            rotacionY = 0;
            if (posicion_valida({ pos.x, 0, pos.z - velocidad * velocidad_juego }, { tam.x, 0, tam.z }))
                pos.z -= velocidad * velocidad_juego;
        }
        else {
            rotacionY = 90;
            if (posicion_valida({ pos.x - velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad * velocidad_juego;
        }
    }

    if (rotacion_y_actual < rotacionY) {
        if (abs(rotacion_y_actual - rotacionY) <= 180) {
            rotacion_y_actual += 25;
            if (rotacion_y_actual > rotacionY)
                rotacion_y_actual = rotacionY;
        }
        else {
            rotacion_y_actual -= 25;
            rotacion_y_actual %= 360;
            if (rotacion_y_actual < 0)
                rotacion_y_actual += 360;

            if (rotacion_y_actual < rotacionY)
                rotacion_y_actual = rotacionY;
        }
    }
    else if (rotacion_y_actual > rotacionY) {
        if (abs(rotacion_y_actual - rotacionY) <= 180) {
            rotacion_y_actual -= 25;
            if (rotacion_y_actual < rotacionY)
                rotacion_y_actual = rotacionY;

        }
        else {
            rotacion_y_actual += 25;
            rotacion_y_actual %= 360;

            if (rotacion_y_actual < rotacionY)
                rotacion_y_actual = rotacionY;
        }

    }

    if (moverArriba || moverDerecha || moverIzquierda || moverAbajo) {
        if (balanceandoseDerecha) {
            rotacion_z_actual += 3 * velocidad_juego;
            if (rotacion_z_actual == 12) {
                balanceandoseDerecha = false;
            }
        }
        else {
            rotacion_z_actual -= 3 * velocidad_juego;
            if (rotacion_z_actual == -12) {
                balanceandoseDerecha = true;
            }
        }
    }
    else
        rotacion_z_actual = 0;
}

void bomberman::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(rotacion_y_actual, 0, 1, 0);
    glRotatef(rotacion_z_actual, 0, 0, 1);
    ControladorObjetos::dibujar(OBJ_PLAYER);
    glPopMatrix();
}
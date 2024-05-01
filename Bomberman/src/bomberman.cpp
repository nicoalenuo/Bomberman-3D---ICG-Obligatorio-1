#include "../lib/bomberman.h"

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
bool movimiento;
void bomberman::actualizar() {
    movimiento = false;
    if (moverArriba) {
        if (mouseX >= 45 && mouseX < 135) {
            rotacionY = 90;
            if (atravesar_paredes || posicion_valida({ pos.x - velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad * velocidad_juego;
        }
        else if (mouseX >= 135 && mouseX < 225) {
            rotacionY = 180;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z + velocidad * velocidad_juego }, { tam.x, 0,tam.z }))
                pos.z += velocidad * velocidad_juego;
        }
        else if (mouseX >= 225 && mouseX < 315) {
            rotacionY = 270;
            if (atravesar_paredes || posicion_valida({ pos.x + velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad * velocidad_juego;
        }
        else {
            rotacionY = 0;
            if (atravesar_paredes || posicion_valida({ pos.x, 0,pos.z - velocidad * velocidad_juego }, { tam.x, 0,tam.z }))
                pos.z -= velocidad * velocidad_juego;
        }
        movimiento = true;
    }
    if (moverAbajo) {
        if (mouseX >= 45 && mouseX < 135) {
            rotacionY = 270;
            if (atravesar_paredes || posicion_valida({ pos.x + velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad * velocidad_juego;
        }
        else if (mouseX >= 135 && mouseX < 225) {
            rotacionY = 0;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z - velocidad * velocidad_juego }, { tam.x, 0, tam.z }))
                pos.z -= velocidad * velocidad_juego;
        }
        else if (mouseX >= 225 && mouseX < 315) {
            rotacionY = 90;
            if (atravesar_paredes || posicion_valida({ pos.x - velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad * velocidad_juego;
        }
        else {
            rotacionY = 180;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z + velocidad * velocidad_juego }, { tam.x, 0, tam.z }))
                pos.z += velocidad * velocidad_juego;
        }
        movimiento = true;
    }
    if (moverDerecha) {
        if (mouseX >= 45 && mouseX < 135) {
            rotacionY = 0;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z - velocidad * velocidad_juego }, { tam.x, 0, tam.z }))
                pos.z -= velocidad * velocidad_juego;
        }
        else if (mouseX >= 135 && mouseX < 225) {
            rotacionY = 90;
            if (atravesar_paredes || posicion_valida({ pos.x - velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad * velocidad_juego;
        }
        else if (mouseX >= 225 && mouseX < 315) {
            rotacionY = 180;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z + velocidad * velocidad_juego }, { tam.x, 0, tam.z }))
                pos.z += velocidad * velocidad_juego;
        }
        else {
            rotacionY = 270;
            if (atravesar_paredes || posicion_valida({ pos.x + velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad * velocidad_juego;
        }
        movimiento = true;
    }

    if (moverIzquierda) {
        if (mouseX >= 45 && mouseX < 135) {
            rotacionY = 180;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z + velocidad * velocidad_juego }, { tam.x, 0, tam.z }))
                pos.z += velocidad * velocidad_juego;
        }
        else if (mouseX >= 135 && mouseX < 225) {
            rotacionY = 270;
            if (atravesar_paredes || posicion_valida({ pos.x + velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += velocidad * velocidad_juego;
        }
        else if (mouseX >= 225 && mouseX < 315) {
            rotacionY = 0;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z - velocidad * velocidad_juego }, { tam.x, 0, tam.z }))
                pos.z -= velocidad * velocidad_juego;
        }
        else {
            rotacionY = 90;
            if (atravesar_paredes || posicion_valida({ pos.x - velocidad * velocidad_juego, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= velocidad * velocidad_juego;
        }
        movimiento = true;
    }

    //Rotacion para que mire al lado correcto

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

    //Balanceo de izquierda a derecha
    
    if (moverArriba || moverDerecha || moverIzquierda || moverAbajo){
        if (balanceandoseDerecha) {
            rotacion_z_actual += 2 * velocidad_juego;
            if (rotacion_z_actual > 8) {
                balanceandoseDerecha = false;
            }
        }
        else {
            rotacion_z_actual -= 2 * velocidad_juego;
            if (rotacion_z_actual < -8) {
                balanceandoseDerecha = true;
            }
        }
    }
    else {
        rotacion_z_actual = 0;
    }

    //Sonido de pisadas
    if (movimiento) {
        pasos++;
    }

    if (pasos >= 10) {
        pasos = 0;
        ControladorAudio::playAudio(sonido::pasos);
    }

    //Chequeo con fuego

    if (!inmortal && !ControladorPoderes::getEstaActivo(INMORTALIDAD) && contactoConFuego())
        finJuego = true;
}

void bomberman::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(GLfloat(rotacion_y_actual), 0, 1, 0);
    glRotatef(GLfloat(rotacion_z_actual), 0, 0, 1); 
    ControladorObjetos::dibujar(OBJ_PLAYER);
    glPopMatrix();
}
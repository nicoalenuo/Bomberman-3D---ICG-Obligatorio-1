#include "../lib/bomberman.h"

bomberman::bomberman(vector_3 pos, vector_3 tam, GLfloat velocidad) : personaje(pos, tam, velocidad) {
    vida = 1;
    moverBomba = false; //por el momento esta no se va a utilizar
    largoBomba = 1;
    tiempoBomba = 2000;
    maxBomba = 1;
    cantActual = 0;
    rotacion_y_actual = 0;
    rotacion_z_actual = 0;
    balanceandoseDerecha = false;
    pasos = 0;
}

GLfloat rotacionY, rotacionZ;
bool movimiento;
GLfloat desplazamiento;
void bomberman::actualizar() { //perdon a la persona que tenga que entender esto
    movimiento = false;
    desplazamiento = velocidad * (elapsed_time / frameDelay) * (ControladorPoderes::getEstaActivo(AUMENTAR_VELOCIDAD) ? 2 : 1);
    if (moverArriba) {
        if (ControladorCamara::camaraMiraHacia(EJE_MENOS_X)) {
            rotacionY = 90;
            if (atravesar_paredes || posicion_valida({ pos.x - desplazamiento, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= desplazamiento;
        }
        else if (ControladorCamara::camaraMiraHacia(EJE_Z)) {
            rotacionY = 180;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z + desplazamiento }, { tam.x, 0,tam.z }))
                pos.z += desplazamiento;
        }
        else if (ControladorCamara::camaraMiraHacia(EJE_X)) {
            rotacionY = 270;
            if (atravesar_paredes || posicion_valida({ pos.x + desplazamiento, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += desplazamiento;
        }
        else {
            rotacionY = 0;
            if (atravesar_paredes || posicion_valida({ pos.x, 0,pos.z - desplazamiento }, { tam.x, 0,tam.z }))
                pos.z -= desplazamiento;
        }
        movimiento = true;
    }
    if (moverAbajo) {
        if (ControladorCamara::camaraMiraHacia(EJE_MENOS_X)) {
            rotacionY = 270;
            if (atravesar_paredes || posicion_valida({ pos.x + desplazamiento, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += desplazamiento;
        }
        else if (ControladorCamara::camaraMiraHacia(EJE_Z)) {
            rotacionY = 0;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z - desplazamiento }, { tam.x, 0, tam.z }))
                pos.z -= desplazamiento;
        }
        else if (ControladorCamara::camaraMiraHacia(EJE_X)) {
            rotacionY = 90;
            if (atravesar_paredes || posicion_valida({ pos.x - desplazamiento, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= desplazamiento;
        }
        else {
            rotacionY = 180;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z + desplazamiento }, { tam.x, 0, tam.z }))
                pos.z += desplazamiento;
        }
        movimiento = true;
    }
    if (moverDerecha) {
        if (ControladorCamara::camaraMiraHacia(EJE_MENOS_X)) {
            rotacionY = 0;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z - desplazamiento }, { tam.x, 0, tam.z }))
                pos.z -= desplazamiento;
        }
        else if (ControladorCamara::camaraMiraHacia(EJE_Z)) {
            rotacionY = 90;
            if (atravesar_paredes || posicion_valida({ pos.x - desplazamiento, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= desplazamiento;
        }
        else if (ControladorCamara::camaraMiraHacia(EJE_X)) {
            rotacionY = 180;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z + desplazamiento }, { tam.x, 0, tam.z }))
                pos.z += desplazamiento;
        }
        else {
            rotacionY = 270;
            if (atravesar_paredes || posicion_valida({ pos.x + desplazamiento, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += desplazamiento;
        }
        movimiento = true;
    }

    if (moverIzquierda) {
        if (ControladorCamara::camaraMiraHacia(EJE_MENOS_X)) {
            rotacionY = 180;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z + desplazamiento }, { tam.x, 0, tam.z }))
                pos.z += desplazamiento;
        }
        else if (ControladorCamara::camaraMiraHacia(EJE_Z)) {
            rotacionY = 270;
            if (atravesar_paredes || posicion_valida({ pos.x + desplazamiento, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += desplazamiento;
        }
        else if (ControladorCamara::camaraMiraHacia(EJE_X)) {
            rotacionY = 0;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z - desplazamiento }, { tam.x, 0, tam.z }))
                pos.z -= desplazamiento;
        }
        else {
            rotacionY = 90;
            if (atravesar_paredes || posicion_valida({ pos.x - desplazamiento, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= desplazamiento;
        }
        movimiento = true;
    }

    //Rotacion para que mire al lado correcto

    if (rotacion_y_actual < rotacionY) {
        if (abs(rotacion_y_actual - rotacionY) <= 180) {
            rotacion_y_actual += GLfloat(25 * (elapsed_time / frameDelay));
            if (rotacion_y_actual > rotacionY)
                rotacion_y_actual = rotacionY;
        }
        else {
            rotacion_y_actual -= 25 * (elapsed_time / frameDelay);
            rotacion_y_actual = GLfloat(fmod(rotacion_y_actual, 360));
            if (rotacion_y_actual < 0)
                rotacion_y_actual += 360;

            if (rotacion_y_actual < rotacionY)
                rotacion_y_actual = rotacionY;
        }
    }
    else if (rotacion_y_actual > rotacionY) {
        if (abs(rotacion_y_actual - rotacionY) <= 180) {
            rotacion_y_actual -= 25 * (elapsed_time / frameDelay);
            if (rotacion_y_actual < rotacionY)
                rotacion_y_actual = rotacionY;

        }
        else {
            rotacion_y_actual += 25;
            rotacion_y_actual = GLfloat(fmod(rotacion_y_actual, 360));

            if (rotacion_y_actual < rotacionY)
                rotacion_y_actual = rotacionY;
        }

    }

    //Balanceo de izquierda a derecha
    
    if (moverArriba || moverDerecha || moverIzquierda || moverAbajo){
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
    }
    else {
        rotacion_z_actual = 0;
    }

    //Sonido de pisadas
    if (movimiento)
        pasos += elapsed_time / frameDelay;
    else
        pasos = 0;

    if (pasos >= 12) {
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
    glRotatef(rotacion_y_actual, 0, 1, 0);
    glRotatef(rotacion_z_actual, 0, 0, 1); 
    ControladorObjetos::dibujar(OBJ_PLAYER);
    glPopMatrix();
}
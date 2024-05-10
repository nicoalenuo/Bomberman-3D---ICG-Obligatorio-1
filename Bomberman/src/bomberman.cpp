#include "../lib/bomberman.h"

bomberman::bomberman(vector_3 pos, vector_3 tam, GLfloat velocidad) : personaje(pos, tam, velocidad) {
    moverBomba = false; //por el momento esta no se va a utilizar
    cantActual = 0;
    rotacion_y_actual = 0;
    rotacion_z_actual = 0;
    balanceandoseDerecha = false;
    pasos = 0;
}

GLfloat rotacionY, rotacionZ;
void bomberman::actualizar() { //perdon a la persona que tenga que entender esto
    random_device rdVelocidadParticulaTierra;
    mt19937 genVelocidadParticulaTierra(rdVelocidadParticulaTierra());
    uniform_real_distribution<> disVelocidadParticulaTierra(-0.1, 0.1);

    bool movimiento = false;
    GLfloat desplazamiento = velocidad * (tiempo_entre_frames / frameDelay) * (ControladorPoderes::getInstance()->getValor(AUMENTAR_VELOCIDAD) ? 2 : 1);
    
    
    if (moverArriba) {
        if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_MENOS_X)) {
            rotacionY = 90;
            if (atravesar_paredes || posicion_valida({ pos.x - desplazamiento, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= desplazamiento;
        }
        else if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_Z)) {
            rotacionY = 180;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z + desplazamiento }, { tam.x, 0,tam.z }))
                pos.z += desplazamiento;
        }
        else if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_X)) {
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
        if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_MENOS_X)) {
            rotacionY = 270;
            if (atravesar_paredes || posicion_valida({ pos.x + desplazamiento, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += desplazamiento;
        }
        else if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_Z)) {
            rotacionY = 0;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z - desplazamiento }, { tam.x, 0, tam.z }))
                pos.z -= desplazamiento;
        }
        else if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_X)) {
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
        if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_MENOS_X)) {
            rotacionY = 0;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z - desplazamiento }, { tam.x, 0, tam.z }))
                pos.z -= desplazamiento;
        }
        else if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_Z)) {
            rotacionY = 90;
            if (atravesar_paredes || posicion_valida({ pos.x - desplazamiento, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x -= desplazamiento;
        }
        else if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_X)) {
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
        if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_MENOS_X)) {
            rotacionY = 180;
            if (atravesar_paredes || posicion_valida({ pos.x, 0, pos.z + desplazamiento }, { tam.x, 0, tam.z }))
                pos.z += desplazamiento;
        }
        else if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_Z)) {
            rotacionY = 270;
            if (atravesar_paredes || posicion_valida({ pos.x + desplazamiento, 0, pos.z }, { tam.x, 0, tam.z }))
                pos.x += desplazamiento;
        }
        else if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_X)) {
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
            rotacion_y_actual += GLfloat(25 * (tiempo_entre_frames / frameDelay));
            if (rotacion_y_actual > rotacionY)
                rotacion_y_actual = rotacionY;
        }
        else {
            rotacion_y_actual -= 25 * (tiempo_entre_frames / frameDelay);
            rotacion_y_actual = GLfloat(fmod(rotacion_y_actual, 360));
            if (rotacion_y_actual < 0)
                rotacion_y_actual += 360;

            if (rotacion_y_actual < rotacionY)
                rotacion_y_actual = rotacionY;
        }
    }
    else if (rotacion_y_actual > rotacionY) {
        if (abs(rotacion_y_actual - rotacionY) <= 180) {
            rotacion_y_actual -= 25 * (tiempo_entre_frames / frameDelay);
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
            rotacion_z_actual += 2 * (tiempo_entre_frames / frameDelay);
            if (rotacion_z_actual > 8) {
                balanceandoseDerecha = false;
            }
        }
        else {
            rotacion_z_actual -= 2 * (tiempo_entre_frames / frameDelay);
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
        pasos += tiempo_entre_frames / frameDelay;
    else
        pasos = 0;

    if (pasos >= 12) {
        pasos = 0;
        ControladorAudio::getInstance()->playAudio(sonido::pasos);

        for (int i = 0; i < 10; i++) {
            particulas.push_back(new particula_tierra(
                pos,
                { GLfloat(0.05f), GLfloat(0.05f), GLfloat(0.05f) },
                { 0, -25, 0 },
                { GLfloat(disVelocidadParticulaTierra(genVelocidadParticulaTierra)), 5, GLfloat(disVelocidadParticulaTierra(genVelocidadParticulaTierra)) },
                ControladorTexturas::getInstance()->getTextura(TEXTURA_SUELO)
                )
            );
        }
    }

    //Chequeo con fuego
    if (!inmortal && !ControladorPoderes::getInstance()->getValor(INMORTALIDAD) && contactoConFuego())
        finJuego = true;
}

void bomberman::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(rotacion_y_actual, 0, 1, 0);
    glRotatef(rotacion_z_actual, 0, 0, 1); 
    ControladorObjetos::getInstance()->dibujar(OBJ_PLAYER, 1.0f);
    glPopMatrix();
}
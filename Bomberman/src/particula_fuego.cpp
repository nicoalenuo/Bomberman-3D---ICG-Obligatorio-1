#include "../lib/particula_fuego.h"

random_device rdColorFuego;
mt19937 genColorFuego(rdColorFuego());
uniform_real_distribution<> disColorFuego(0, 1);
particula_fuego::particula_fuego(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel) : particula(pos, tam, ac, vel) {
    if (disColorFuego(genColorFuego) < 0.2) {
        tipoColor = FUEGO_AMARILLO;
        color[0] = 0.9f;
        color[1] = 0.9f;
        color[2] = 0.0f;
    }
    else {
        tipoColor = FUEGO_ROJO;
        color[0] = 0.9f;
        color[1] = 0.2f;
        color[2] = 0.0f;
    }
}

GLfloat tiempoSegundosParticulaFuego;
void particula_fuego::actualizar() {
    if ((pos.y < 2 * tile_size && tipoColor == FUEGO_ROJO) || (pos.y < 1)) {
        tiempoSegundosParticulaFuego = tiempoParticula / 1000.0f;

        pos.x = pos.x + velocidad.x * (elapsed_time / frameDelay);
        pos.y = (aceleracion.y * tiempoSegundosParticulaFuego * tiempoSegundosParticulaFuego) + (velocidad.y * tiempoSegundosParticulaFuego) + pos_inicial.y;
        pos.z = pos.z + velocidad.z * (elapsed_time / frameDelay);

        tiempoParticula += elapsed_time ;
    }
    else {
        eliminar = true;
    }

    if (pos.x < 0 || pos.z < 0 || pos.x > largoTablero * tile_size || pos.z > anchoTablero * tile_size)
        eliminar = true;
}

void particula_fuego::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    ControladorObjetos::dibujarCubo(tam, 0, color);
    glPopMatrix();
}
#include "../lib/particula_bonificador.h"

particula_bonificador::particula_bonificador(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel) : particula(pos, tam, ac, vel) {
   
}

GLfloat tiempoSegundosParticulaBonificador;
void particula_bonificador::actualizar() {
    if (pos.y < 10 * tile_size) {
        tiempoSegundosParticulaBonificador = tiempoParticula / 1000.0f;

        pos.x = pos.x + velocidad.x * (tiempo_entre_frames / frameDelay);
        pos.y = (aceleracion.y * tiempoSegundosParticulaBonificador * tiempoSegundosParticulaBonificador) + (velocidad.y * tiempoSegundosParticulaBonificador) + pos_inicial.y;
        pos.z = pos.z + velocidad.z * (tiempo_entre_frames / frameDelay);

        tiempoParticula += tiempo_entre_frames;
    }
    else {
        eliminar = true;
    }

    if (pos.x < 0 || pos.z < 0 || pos.x > largoTablero * tile_size || pos.z > anchoTablero * tile_size)
        eliminar = true;
}

GLfloat colorParticulaBonificador[3] = { 1.0f, 1.0f, 0.5f };
void particula_bonificador::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    ControladorObjetos::getInstance()->dibujarCubo(tam, 0, colorParticulaBonificador);
    glPopMatrix();
}
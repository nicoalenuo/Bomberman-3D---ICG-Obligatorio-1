#include "../lib/particula_enemigo_derrotado.h"

particula_enemigo_derrotado::particula_enemigo_derrotado(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel) : particula(pos, tam, ac, vel) {

}

void particula_enemigo_derrotado::actualizar() {
    if (pos.y > 0.0f) {
        pos.x = pos.x + velocidad.x * (tiempo_entre_frames / frameDelay);

        pos.y = aceleracion.y * tiempoParticula * tiempoParticula / ( 1000.0f * 1000.0f) +
            velocidad.y * tiempoParticula / 1000.0f +
            pos_inicial.y;

        pos.z = pos.z + velocidad.z * (tiempo_entre_frames / frameDelay);
        tiempoParticula += tiempo_entre_frames;
    }

    if (pos.x < 0 || pos.y < 0 || pos.z < 0 || pos.x > largoTablero * tile_size || pos.z > anchoTablero * tile_size)
        eliminar = true;
}

void particula_enemigo_derrotado::dibujar() {
    GLfloat color[3] = { 0.5f, 0.0f, 0.0f };
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(pos.x, pos.y, pos.z);
    ControladorObjetos::getInstance()->dibujarCubo(tam, 0, color);
    glPopMatrix();
}

#include "../lib/particula_fuego.h"

random_device rdColorFuego;
mt19937 genColorFuego(rdColorFuego());
uniform_real_distribution<> disColorFuego(0, 1);
particula_fuego::particula_fuego(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel) : particula(pos, tam, ac, vel) {
    if (disColorFuego(genColorFuego) < 0.2)
        color = FUEGO_AMARILLO;
    else
        color = FUEGO_ROJO;
}

GLfloat tiempoSegundosParticulaFuego;
void particula_fuego::actualizar() {
    if ((pos.y < 2 * tile_size && color == FUEGO_ROJO) || (pos.y < 1)) {
        tiempoSegundosParticulaFuego = tiempoParticula / 1000.0f;

        pos.x = pos.x + velocidad.x;
        pos.y = (aceleracion.y * tiempoSegundosParticulaFuego * tiempoSegundosParticulaFuego) + (velocidad.y * tiempoSegundosParticulaFuego) + pos_inicial.y;
        pos.z = pos.z + velocidad.z;

        tiempoParticula += frameDelay;
    }
    else {
        eliminar = true;
    }

    if (pos.x < 0 || pos.z < 0 || pos.x > largoTablero * tile_size || pos.z > anchoTablero * tile_size)
        eliminar = true;
}

void particula_fuego::dibujar() {
    glPushMatrix();

    switch (color) {
    case FUEGO_ROJO:
        glColor3f(0.9f, 0.2f, 0.0f);
        break;
    case FUEGO_AMARILLO:
        glColor3f(0.9f, 0.9f, 0.0f);
        break;
    }

    glTranslatef(pos.x, pos.y, pos.z);

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
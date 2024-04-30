#include "../lib/particula_bonificador.h"

particula_bonificador::particula_bonificador(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel) : particula(pos, tam, ac, vel) {
   
}

GLfloat tiempoSegundosParticulaBonificador;
void particula_bonificador::actualizar() {
    if (pos.y < 10 * tile_size) {
        tiempoSegundosParticulaBonificador = tiempoParticula / 1000.0f;

        pos.x = pos.x + velocidad.x;
        pos.y = (aceleracion.y * tiempoSegundosParticulaBonificador * tiempoSegundosParticulaBonificador) + (velocidad.y * tiempoSegundosParticulaBonificador) + pos_inicial.y;
        pos.z = pos.z + velocidad.z;

        tiempoParticula += frameDelay;
    }
    else {
        eliminar = true;
    }

    if (pos.x < 0 || pos.z < 0 || pos.x > largoTablero * tile_size || pos.z > anchoTablero * tile_size)
        eliminar = true;
}

void particula_bonificador::dibujar() {
    glPushMatrix();

    glTranslatef(pos.x, pos.y, pos.z);
    glColor3f(1.0f, 1.0f, 0.5f);
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

    if (texturas_habilitadas)
        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
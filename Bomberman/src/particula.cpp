#include "../lib/particula.h"

random_device rdColorFuego;
mt19937 genColorFuego(rdColorFuego());
uniform_real_distribution<> disColorFuego(0, 1);
particula::particula(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel, GLuint textura, tipo_particula tipo) : objeto(pos, tam) {
    eliminar = false;
    tiempoParticula = 0;
    tiempoEliminacion = 0;
    pos_inicial = pos;
    aceleracion = ac;
    velocidad = vel;
    this->textura = textura;
    this->tipo = tipo;


    if (tipo == PARTICULA_FUEGO) {
        double random = disColorFuego(genColorFuego);
        if (random < 0.85) {//rojo
            color[0] = 0.9f;
            color[1] = 0.1f;
            color[2] = 0.0f;
        }
        else { //amarillo
            color[0] = 0.9f;
            color[1] = 0.9f;
            color[2] = 0.0f;
        }
    }
}

GLfloat tiempoSegundos;
void particula::actualizar() {
    switch (tipo) {
    case PARTICULA_ESTRUCTURA_DESTRUCTIBLE:
        if (pos.y > 0.2f) {
            tiempoSegundos = tiempoParticula / 1000.0f;
            pos.x = pos.x + velocidad.x;

            pos.y = max(aceleracion.y * tiempoSegundos * tiempoSegundos +
                velocidad.y * tiempoSegundos +
                pos_inicial.y, 0.2f);

            pos.z = pos.z + velocidad.z;
            tiempoParticula += frameDelay;
        }
        else {
            tiempoEliminacion += frameDelay * velocidad_juego;
            if (tiempoEliminacion > 4000) { //para que caigan al suelo, y queden ahi por 3 segundos
                eliminar = true;
            }
        }
        break;
    case PARTICULA_FUEGO:
        if ((pos.y < 2 * tile_size && color[1] == 0.1f) || (pos.y < 1)) {
            tiempoSegundos = tiempoParticula / 1000.0f;

            pos.x = pos.x + velocidad.x;
            pos.y = (aceleracion.y * tiempoSegundos * tiempoSegundos) + (velocidad.y * tiempoSegundos) + pos_inicial.y;
            pos.z = pos.z + velocidad.z;

            tiempoParticula += frameDelay;
        }
        else {
            eliminar = true;
        }
        break;
    }

    if (pos.x < 0 || pos.z < 0 || pos.x > largoTablero * tile_size || pos.z > anchoTablero * tile_size)
        eliminar = true;
}

void particula::dibujar() {
    glPushMatrix();

    switch (tipo) {
    case PARTICULA_ESTRUCTURA_DESTRUCTIBLE:
        if (texturas_habilitadas) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textura);
            glColor3f(1.0f, 1.0f, 1.0f);
        }
        break;
    case PARTICULA_FUEGO:
        glColor3f(color[0], color[1], color[2]);
        break;
    }

    glTranslatef(pos.x, pos.y, pos.z);

    glBegin(GL_QUADS);

    //Cara de abajo
    glTexCoord2f(0, 0);
    glVertex3f(-tam.x, 0, -tam.z);

    glTexCoord2f(0, 0.2f);
    glVertex3f(tam.x, 0, -tam.z);

    glTexCoord2f(0.2f, 0.2f);
    glVertex3f(tam.x, 0, tam.z);

    glTexCoord2f(0.2f, 0);
    glVertex3f(-tam.x, 0, tam.z);

    // Cara de arriba
    glTexCoord2f(0, 0);
    glVertex3f(-tam.x, tam.y, -tam.z);

    glTexCoord2f(0, 0.2f);
    glVertex3f(tam.x, tam.y, -tam.z);

    glTexCoord2f(0.2f, 0.2f);
    glVertex3f(tam.x, tam.y, tam.z);

    glTexCoord2f(0.2f, 0);
    glVertex3f(-tam.x, tam.y, tam.z);

    // Cara de atras
    glTexCoord2f(0, 0);
    glVertex3f(-tam.x, 0, -tam.z);

    glTexCoord2f(0, 0.2f);
    glVertex3f(tam.x, 0, -tam.z);

    glTexCoord2f(0.2f, 0.2f);
    glVertex3f(tam.x, tam.y, -tam.z);

    glTexCoord2f(0.2f, 0);
    glVertex3f(-tam.x, tam.y, -tam.z);

    // Cara de adelante
    glTexCoord2f(0, 0);
    glVertex3f(-tam.x, 0, tam.z);

    glTexCoord2f(0, 0.2f);
    glVertex3f(tam.x, 0, tam.z);

    glTexCoord2f(0.2f, 0.2f);
    glVertex3f(tam.x, tam.y, tam.z);

    glTexCoord2f(0.2f, 0);
    glVertex3f(-tam.x, tam.y, tam.z);

    // Cara izquierda
    glTexCoord2f(0, 0);
    glVertex3f(-tam.x, 0, -tam.z);

    glTexCoord2f(0, 0.2f);
    glVertex3f(-tam.x, 0, tam.z);

    glTexCoord2f(0.2f, 0.2f);
    glVertex3f(-tam.x, tam.y, tam.z);

    glTexCoord2f(0.2f, 0);
    glVertex3f(-tam.x, tam.y, -tam.z);

    // Cara derecha 
    glTexCoord2f(0, 0);
    glVertex3f(tam.x, 0, -tam.z);

    glTexCoord2f(0, 0.2f);
    glVertex3f(tam.x, 0, tam.z);

    glTexCoord2f(0.2f, 0.2f);
    glVertex3f(tam.x, tam.y, tam.z);

    glTexCoord2f(0.2f, 0);
    glVertex3f(tam.x, tam.y, -tam.z);

    glEnd();

    if (texturas_habilitadas) 
        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
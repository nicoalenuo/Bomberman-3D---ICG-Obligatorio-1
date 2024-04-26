#include "../lib/particula.h"

particula::particula(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel, GLuint textura) : objeto(pos, tam) {
    eliminar = false;
    tiempoParticula = 0;
    tiempoEliminacion = 0;
    pos_y_inicial = pos.y;
    this->ac = ac;
    this->vel = vel;
    this->textura = textura;
}

GLfloat tiempoSegundos;
void particula::actualizar() {
    if (pos.y > 0.2f) {
        tiempoSegundos = tiempoParticula / 1000.0f;
        pos.x = pos.x + vel.x;
        pos.y = max(ac.y * tiempoSegundos * tiempoSegundos +
            vel.y * tiempoSegundos +
            pos_y_inicial, 0.2f);
        pos.z = pos.z + vel.z;
        tiempoParticula += frameDelay;
    }
    else {
        tiempoEliminacion += frameDelay * velocidad_juego;
        if (tiempoEliminacion > 2000) {
            eliminar = true;
        }
    }

    if (pos.x < 0 || pos.z < 0 || pos.x > largoTablero * tile_size || pos.z > anchoTablero * tile_size)
        eliminar = true;
}

void particula::dibujar() {
    if (texturas_habilitadas) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura);
        glColor3f(1.0f, 1.0f, 1.0f);
    }


    glPushMatrix();
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
    glPopMatrix();

    glDisable(GL_BLEND);

    if (texturas_habilitadas) 
        glDisable(GL_TEXTURE_2D);
}
#include "../lib/particula_estructura.h"

particula_estructura::particula_estructura(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel, GLuint textura) : particula(pos, tam, ac, vel) {
    tiempoEliminacion = 0;
    color_alpha = 1.0f;
    this->textura = textura;
}

void particula_estructura::actualizar() {
    if (pos.y > 0.1f) {
        pos.x = pos.x + velocidad.x * (tiempo_entre_frames / frameDelay);

        pos.y = max(aceleracion.y * tiempoParticula * tiempoParticula / (1000.0f * 1000.0f) +
            velocidad.y * tiempoParticula / 1000.0f +
            pos_inicial.y, 0.1f);

        pos.z = pos.z + velocidad.z * (tiempo_entre_frames / frameDelay);
        tiempoParticula += tiempo_entre_frames;
    }
    else {
        if (tiempoEliminacion > 4000) {
            if (color_alpha > 0.0f) {
                color_alpha -= 0.02f * tiempo_entre_frames / frameDelay;
            }
            else {
                eliminar = true;
            }
        }
        else {
            tiempoEliminacion += int(tiempo_entre_frames);
        }
    }

    if (pos.x < 0 || pos.z < 0 || pos.x > largoTablero * tile_size || pos.z > anchoTablero * tile_size)
        eliminar = true;
}

void particula_estructura::dibujar() {
    glPushMatrix();

    glColor3f(0.56f, 0.0f, 0.25f);

    if (texturas_habilitadas) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura);
        glColor4f(1.f, 1.f, 1.f, color_alpha);
    }

    glTranslatef(pos.x, pos.y, pos.z);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    glDisable(GL_BLEND);

    if (texturas_habilitadas)
        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

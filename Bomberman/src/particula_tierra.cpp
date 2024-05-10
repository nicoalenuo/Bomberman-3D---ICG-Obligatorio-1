#include "../lib/particula_tierra.h"


particula_tierra::particula_tierra(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel, GLuint textura) : particula(pos, tam, ac, vel) {
    this->textura = textura;
}

void particula_tierra::actualizar() {
    if (pos.y >= 0)  {
        pos.x = pos.x + velocidad.x * (tiempo_entre_frames / frameDelay);
        pos.y = (aceleracion.y * tiempoParticula * tiempoParticula / (1000.0f * 1000.0f)) + (velocidad.y * (tiempoParticula / 1000.0f)) + pos_inicial.y;
        pos.z = pos.z + velocidad.z * (tiempo_entre_frames / frameDelay);

        tiempoParticula += tiempo_entre_frames;
    }
    else {
        eliminar = true;
    }

    if (pos.x < 0 || pos.z < 0 || pos.x > largoTablero * tile_size || pos.z > anchoTablero * tile_size)
        eliminar = true;
}

void particula_tierra::dibujar() {
    glPushMatrix();

    glColor3f(144.f / 255.f, 12.f / 255.f, 63.f / 255.f);

    if (texturas_habilitadas) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura);
        glColor3f(1.f, 1.f, 1.f);
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
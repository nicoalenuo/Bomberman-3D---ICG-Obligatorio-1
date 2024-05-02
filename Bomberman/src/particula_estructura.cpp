#include "../lib/particula_estructura.h"

particula_estructura::particula_estructura(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel, GLuint textura) : particula(pos, tam, ac, vel) {
    tiempoEliminacion = 0;
    this->textura = textura;
}

GLfloat tiempoSegundos;
void particula_estructura::actualizar() {
    if (pos.y > 0.1f) {
        tiempoSegundos = tiempoParticula / 1000.0f;
        pos.x = pos.x + velocidad.x * (elapsed_time / frameDelay);

        pos.y = max(aceleracion.y * tiempoSegundos * tiempoSegundos +
            velocidad.y * tiempoSegundos +
            pos_inicial.y, 0.1f);

        pos.z = pos.z + velocidad.z * (elapsed_time / frameDelay);
        tiempoParticula += elapsed_time;
    }
    else {
        tiempoEliminacion += int(elapsed_time);
        if (tiempoEliminacion > 4000) //para que caigan al suelo, y queden ahi por 4 segundos
            eliminar = true;
    }

    if (pos.x < 0 || pos.z < 0 || pos.x > largoTablero * tile_size || pos.z > anchoTablero * tile_size)
        eliminar = true;
}

void particula_estructura::dibujar() {
    glPushMatrix();

    if (texturas_habilitadas) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura);
    }
    glColor3f(1.0f, 1.0f, 1.0f);

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

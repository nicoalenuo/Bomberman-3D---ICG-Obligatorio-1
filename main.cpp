#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <set>
#include "OpenGL-basico/src/bloque-destructible.cpp"
#include "OpenGL-basico/lib/controlador.h"

using namespace std;

const float lado = 2.0f;

void construir_bloque(bloque_destructible bloque) {
    glBegin(GL_QUADS);

    // Cara frontal (z = lado/2)
    glColor3f(1.0f, 0.0f, 0.0f); // Rojo

    glVertex3f(-lado / 2 + bloque.getPosX(), 0, lado / 2 + bloque.getPosZ());
    glVertex3f(lado / 2 + bloque.getPosX(), 0, lado / 2 + bloque.getPosZ());
    glVertex3f(lado / 2 + bloque.getPosX(), lado, lado / 2 + bloque.getPosZ());
    glVertex3f(-lado / 2 + bloque.getPosX(), lado, lado / 2 + bloque.getPosZ());

    glVertex3f(-lado / 2 + bloque.getPosX(), 0, -lado / 2 + bloque.getPosZ());
    glVertex3f(lado / 2 + bloque.getPosX(), 0, -lado / 2 + bloque.getPosZ());
    glVertex3f(lado / 2 + bloque.getPosX(), lado, -lado / 2 + bloque.getPosZ());
    glVertex3f(-lado / 2 + bloque.getPosX(), lado, -lado / 2 + bloque.getPosZ());

    glVertex3f(-lado / 2 + bloque.getPosX(), lado, -lado / 2 + bloque.getPosZ());
    glVertex3f(lado / 2 + bloque.getPosX(), lado, -lado / 2 + bloque.getPosZ());
    glVertex3f(lado / 2 + bloque.getPosX(), lado, lado / 2 + bloque.getPosZ());
    glVertex3f(-lado / 2 + bloque.getPosX(), lado, lado / 2 + bloque.getPosZ());

    glVertex3f(-lado / 2 + bloque.getPosX(), 0, -lado / 2 + bloque.getPosZ());
    glVertex3f(lado / 2 + bloque.getPosX(), 0, -lado / 2 + bloque.getPosZ());
    glVertex3f(lado / 2 + bloque.getPosX(), 0, lado / 2 + bloque.getPosZ());
    glVertex3f(-lado / 2 + bloque.getPosX(), 0, lado / 2 + bloque.getPosZ());

    glVertex3f(-lado / 2 + bloque.getPosX(), 0, -lado / 2 + bloque.getPosZ());
    glVertex3f(-lado / 2 + bloque.getPosX(), 0, lado / 2 + bloque.getPosZ());
    glVertex3f(-lado / 2 + bloque.getPosX(), lado, lado / 2 + bloque.getPosZ());
    glVertex3f(-lado / 2 + bloque.getPosX(), lado, -lado / 2 + bloque.getPosZ());

    glVertex3f(lado / 2 + bloque.getPosX(), 0, -lado / 2 + bloque.getPosZ());
    glVertex3f(lado / 2 + bloque.getPosX(), 0, lado / 2 + bloque.getPosZ());
    glVertex3f(lado / 2 + bloque.getPosX(), lado, lado / 2 + bloque.getPosZ());
    glVertex3f(lado / 2 + bloque.getPosX(), lado, -lado / 2 + bloque.getPosZ());

    glEnd(); // Finalizar el dibujo del cubo
}

int main(int argc, char* argv[]) {
    Controlador* controlador = Controlador::getInstance();

    GLfloat posX = 20.0;
    GLfloat posZ = 20.0;

    GLfloat posXreal = 20.0;
    GLfloat posZreal = 20.0;

    float radius = 20.0f;

    float angleRadians = (*controlador).getMouseX() * (3.14159f / 180.0f); 

    float camX = posXreal + radius * sin(angleRadians);
    float camZ = posZreal + radius * cos(angleRadians);

    Uint32 startTime = SDL_GetTicks(); // Obtener el tiempo inicial
    Uint32 currentTime = SDL_GetTicks(); // Obtener el tiempo actual

    set<bloque_destructible*> bloques; //Para colocar mas bloques xd
    bloques.insert(new bloque_destructible(1, 1));
    bloques.insert(new bloque_destructible(7, 14));
    bloques.insert(new bloque_destructible(-14, -2));

    (*controlador).inicializar();

    do {
        angleRadians = (*controlador).getMouseX() * (3.14159f / 180.0f);
        camX = posXreal + radius * sin(angleRadians);
        camZ = posZreal + radius * cos(angleRadians);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        gluLookAt(camX, 30, camZ, posXreal, 0, posZreal, 0, 1, 0);

        glBegin(GL_QUADS);

        glColor3f(227.0 / 255.0, 186.0 / 255.0, 143.0 / 255.0);
        glVertex3f(20., 0., 20.);
        glVertex3f(20., 0., -20.);
        glVertex3f(-20., 0., -20.);
        glVertex3f(-20., 0., 20.);
        glEnd();

        if ((*controlador).getMoverArriba() && posX == posXreal && posZ == posZreal) {
            if ((*controlador).getMouseX() >= 45 && (*controlador).getMouseX() < 135) 
                posX -= lado;;
            if ((*controlador).getMouseX() >= 135 && (*controlador).getMouseX() < 225) 
                posZ += lado;;
            if ((*controlador).getMouseX() >= 225 && (*controlador).getMouseX() < 315) 
                posX += lado;;
            if ((*controlador).getMouseX()  >=315 || (*controlador).getMouseX() < 45) 
                posZ -= lado;;
        }
        if ((*controlador).getMoverAbajo() && posX == posXreal && posZ == posZreal) {
            if ((*controlador).getMouseX() >= 45 && (*controlador).getMouseX() < 135) 
                posX += lado;;
            if ((*controlador).getMouseX() >= 135 && (*controlador).getMouseX() < 225)
                posZ -= lado;;
            if ((*controlador).getMouseX() >= 225 && (*controlador).getMouseX() < 315)
                posX -= lado;;
            if ((*controlador).getMouseX() >= 315 || (*controlador).getMouseX() < 45)
                posZ += lado;;
        }

        if ((*controlador).getMoverDerecha() && posX == posXreal && posZ == posZreal) {
            if ((*controlador).getMouseX() >= 45 && (*controlador).getMouseX() < 135) 
                posZ -= lado;;
            if ((*controlador).getMouseX() >= 135 && (*controlador).getMouseX() < 225) 
                posX -= lado;;
            if ((*controlador).getMouseX() >= 225 && (*controlador).getMouseX() < 315) 
                posZ += lado;;
            if ((*controlador).getMouseX() >= 315 || (*controlador).getMouseX() < 45)
                posX += lado;;
        }

        if ((*controlador).getMoverIzquierda() && posX == posXreal && posZ == posZreal) {
            if ((*controlador).getMouseX() >= 45 && (*controlador).getMouseX() < 135) 
                posZ += lado;;
            if ((*controlador).getMouseX() >= 135 && (*controlador).getMouseX() < 225) 
                posX += lado;;
            if ((*controlador).getMouseX() >= 225 && (*controlador).getMouseX() < 315) 
                posZ -= lado;;
            if ((*controlador).getMouseX() >= 315 || (*controlador).getMouseX() < 45)
                posX -= lado;;
        }

        if (posXreal < posX) 
            posXreal += 0.1;
        if (posXreal > posX) 
            posXreal -= 0.1;
        if (posZreal < posZ) 
            posZreal += 0.1;
        if (posZreal > posZ) 
            posZreal -= 0.1;

        if (abs(posXreal - posX) < 0.11) 
            posXreal = posX;
        if (abs(posZreal - posZ) < 0.11) 
            posZreal = posZ;

        for (std::set<bloque_destructible*>::iterator it = bloques.begin(); it != bloques.end(); ++it) {
            bloque_destructible* ptr_bloque = *it;
            
            construir_bloque(*ptr_bloque);
        }

        glBegin(GL_QUADS);

        // Cara frontal (z = lado/2)
        glColor3f(1.0f, 0.0f, 0.0f); // Rojo
        glVertex3f(-lado / 2 + posXreal, 0, lado / 2 + posZreal);
        glVertex3f(lado / 2 + posXreal, 0, lado / 2 + posZreal);
        glVertex3f(lado / 2 + posXreal, lado, lado / 2 + posZreal);
        glVertex3f(-lado / 2 + posXreal, lado, lado / 2 + posZreal);

        // Cara posterior (z = -lado/2)
        glColor3f(0.0f, 1.0f, 0.0f); // Verde
        glVertex3f(-lado / 2 + posXreal, 0, -lado / 2 + posZreal);
        glVertex3f(lado / 2 + posXreal, 0, -lado / 2 + posZreal);
        glVertex3f(lado / 2 + posXreal, lado, -lado / 2 + posZreal);
        glVertex3f(-lado / 2 + posXreal, lado, -lado / 2 + posZreal);

        // Cara superior (y = lado/2)
        glColor3f(0.0f, 0.0f, 1.0f); // Azul
        glVertex3f(-lado / 2 + posXreal, lado, -lado / 2 + posZreal);
        glVertex3f(lado / 2 + posXreal, lado, -lado / 2 + posZreal);
        glVertex3f(lado / 2 + posXreal, lado, lado / 2 + posZreal);
        glVertex3f(-lado / 2 + posXreal, lado, lado / 2 + posZreal);

        // Cara inferior (y = -lado/2)
        glColor3f(1.0f, 1.0f, 0.0f); // Amarillo
        glVertex3f(-lado / 2 + posXreal, 0, -lado / 2 + posZreal);
        glVertex3f(lado / 2 + posXreal, 0, -lado / 2 + posZreal);
        glVertex3f(lado / 2 + posXreal, 0, lado / 2 + posZreal);
        glVertex3f(-lado / 2 + posXreal, 0, lado / 2 + posZreal);

        // Cara izquierda (x = -lado/2)
        glColor3f(1.0f, 0.0f, 1.0f); // Magenta
        glVertex3f(-lado / 2 + posXreal, 0, -lado / 2 + posZreal);
        glVertex3f(-lado / 2 + posXreal, 0, lado / 2 + posZreal);
        glVertex3f(-lado / 2 + posXreal, lado, lado / 2 + posZreal);
        glVertex3f(-lado / 2 + posXreal, lado, -lado / 2 + posZreal);

        // Cara derecha (x = lado/2)
        glColor3f(0.0f, 1.0f, 1.0f); // Cian
        glVertex3f(lado / 2 + posXreal, 0, -lado / 2 + posZreal);
        glVertex3f(lado / 2 + posXreal, 0, lado / 2 + posZreal);
        glVertex3f(lado / 2 + posXreal, lado, lado / 2 + posZreal);
        glVertex3f(lado / 2 + posXreal, lado, -lado / 2 + posZreal);
        glEnd(); 

        (*controlador).manejarEventos();
        (*controlador).actualizar();
    } while (!(*controlador).getFin());

    (*controlador).limpiar();
    return 0;
}

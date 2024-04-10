#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <set>
#include "OpenGL-basico/bloque-destructible.cpp"

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
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    SDL_Window* win = SDL_CreateWindow("ICG-UdelaR",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GLContext context = SDL_GL_CreateContext(win);

    glMatrixMode(GL_PROJECTION);

    glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 1.0f);

    gluPerspective(45, 1280 / 720.f, 1, 200);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);

    bool fin = false;

    SDL_Event evento;

    int mouseX = 0;

    GLfloat posX = 20.0;
    GLfloat posZ = 20.0;

    GLfloat posXreal = 20.0;
    GLfloat posZreal = 20.0;

    bool moverArriba = false;
    bool moverAbajo = false;
    bool moverIzquierda = false;
    bool moverDerecha = false;

    float radius = 20.0f;

    float angleRadians = mouseX * (3.14159f / 180.0f); 

    float camX = posXreal + radius * sin(angleRadians);
    float camZ = posZreal + radius * cos(angleRadians);

    Uint32 startTime = SDL_GetTicks(); // Obtener el tiempo inicial
    Uint32 currentTime = SDL_GetTicks(); // Obtener el tiempo actual

    set<bloque_destructible*> bloques; //Para colocar mas bloques xd
    bloques.insert(new bloque_destructible(1, 1));
    bloques.insert(new bloque_destructible(7, 14));
    bloques.insert(new bloque_destructible(-14, -2));

    do {
        angleRadians = mouseX * (3.14159f / 180.0f);
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

        if (moverArriba && posX == posXreal && posZ == posZreal) {
            if (mouseX >= 45 && mouseX < 135) 
                posX -= lado;;
            if (mouseX >= 135 && mouseX < 225) 
                posZ += lado;;
            if (mouseX >= 225 && mouseX < 315) 
                posX += lado;;
            if (mouseX  >=315 || mouseX < 45) 
                posZ -= lado;;
        }
        if (moverAbajo && posX == posXreal && posZ == posZreal) {
            if (mouseX >= 45 && mouseX < 135) 
                posX += lado;;
            if (mouseX >= 135 && mouseX < 225)
                posZ -= lado;;
            if (mouseX >= 225 && mouseX < 315)
                posX -= lado;;
            if (mouseX >= 315 || mouseX < 45)
                posZ += lado;;
        }

        if (moverDerecha && posX == posXreal && posZ == posZreal) {
            if (mouseX >= 45 && mouseX < 135) 
                posZ -= lado;;
            if (mouseX >= 135 && mouseX < 225) 
                posX -= lado;;
            if (mouseX >= 225 && mouseX < 315) 
                posZ += lado;;
            if (mouseX >= 315 || mouseX < 45)
                posX += lado;;
        }

        if (moverIzquierda && posX == posXreal && posZ == posZreal) {
            if (mouseX >= 45 && mouseX < 135) 
                posZ += lado;;
            if (mouseX >= 135 && mouseX < 225) 
                posX += lado;;
            if (mouseX >= 225 && mouseX < 315) 
                posZ -= lado;;
            if (mouseX >= 315 || mouseX < 45)
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



        //MANEJO DE EVENTOS
        while (SDL_PollEvent(&evento)) {
            switch (evento.type) {
            case SDL_QUIT:
                fin = true;
                break;
            case SDL_KEYDOWN:
                switch (evento.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        fin = true;
                        break;
                    case SDLK_UP:
                        moverArriba = true;
                        break;
                    case SDLK_RIGHT:
                        moverDerecha = true;
                        break;
                    case SDLK_DOWN:
                        moverAbajo = true;
                        break;
                    case SDLK_LEFT:
                        moverIzquierda = true;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (evento.key.keysym.sym) {
                case SDLK_UP:
                    moverArriba = false;
                    break;
                case SDLK_RIGHT:
                    moverDerecha = false;
                    break;
                case SDLK_DOWN:
                    moverAbajo = false;
                    break;
                case SDLK_LEFT:
                    moverIzquierda = false;
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                mouseX = evento.motion.x % 360;
                break;
            }
        }
        SDL_GL_SwapWindow(win);
    } while (!fin);

    // LIMPIEZA
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

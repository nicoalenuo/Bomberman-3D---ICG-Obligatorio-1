#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include "Bomberman/lib/controlador.h"

using namespace std;

int main(int argc, char* argv[]) {
    Controlador* controlador = Controlador::getInstance();

    const int FPS = 30;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    do {
        frameStart = SDL_GetTicks();

        (*controlador).manejarEventos();
        (*controlador).actualizar();
        (*controlador).dibujar();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) 
            SDL_Delay(frameDelay - frameTime);

    } while (!(*controlador).getFin());

    (*controlador).limpiar();
    return 0;
}

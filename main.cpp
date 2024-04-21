#include "Bomberman/lib/controlador.h"

using namespace std;

int main(int argc, char* argv[]) {
    Controlador* controlador = Controlador::getInstance();

    Uint32 frameStart;
    Uint32 frameTime;

    do {
        frameStart = SDL_GetTicks();

        (*controlador).manejarEventos();
        (*controlador).actualizar();
        (*controlador).dibujar();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) 
            SDL_Delay(frameDelay - frameTime);

    } while (!(*controlador).getFin());

    delete controlador;

    return 0;
}

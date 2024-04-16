#include "Bomberman/lib/controlador.h"

using namespace std;

int main(int argc, char* argv[]) {
    Controlador* controlador = Controlador::getInstance();

    const int frameDelay = 33; //33 milisegundos entre cada frame

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

    (*controlador).limpiar();
    delete controlador;

    return 0;
}

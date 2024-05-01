#include "Bomberman/lib/controlador.h"

int main(int argc, char* argv[]) {
    Controlador* controlador = Controlador::getInstance();

    Uint32 frameStart;
    Uint32 frameTime;
    Uint32 segundo = 0;

    do {
        
        frameStart = SDL_GetTicks();

        (*controlador).manejarEventos();
        if (!pausa) {
            (*controlador).actualizar();
        }
        (*controlador).dibujar();

        frameTime = SDL_GetTicks() - frameStart;
        segundo += frameDelay;
        if (frameTime < frameDelay) 
            SDL_Delay(frameDelay - frameTime);

        if (segundo > 1000) { // 1000ms == 1segundo
            if (!pausa && !pararTiempo) 
                disminuirTiempo(1);

            segundo = segundo % 1000;
        }
        

    } while (!fin);

    delete controlador;

    return 0;
}

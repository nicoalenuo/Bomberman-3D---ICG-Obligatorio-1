#include "Bomberman/lib/controlador.h"

int main(int argc, char* argv[]) {
    Controlador* controlador = Controlador::getInstance();

    Uint32 frameStart;
    Uint32 frameTime;
    Uint32 segundo = 0;

    do {
        frameStart = SDL_GetTicks();

        (*controlador).manejarEventos();
        if (!(*controlador).getPausa()) 
            (*controlador).actualizar();
        (*controlador).dibujar();

        frameTime = SDL_GetTicks() - frameStart;
        segundo += frameTime;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
            segundo += frameDelay;
        }
        
        if (segundo > 1000) { // 1000ms == 1segundo
            (*controlador).disminuirTiempo(segundo / 1000);
            segundo = segundo % 1000;
        }

    } while (!(*controlador).getFin() && !(*controlador).getFinJuego());

    if ((*controlador).getFinJuego()) {
        (*controlador).actualizar();
        (*controlador).dibujar();
        SDL_Delay(2000);
    }

    delete controlador;

    return 0;
}

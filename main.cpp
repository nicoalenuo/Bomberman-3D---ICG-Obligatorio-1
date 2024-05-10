#include "Bomberman/lib/controlador.h"

int main(int argc, char* argv[]) {
    Controlador* controlador = Controlador::getInstance();

    do {
        (*controlador).manejarEventos();
        (*controlador).actualizar();
        (*controlador).dibujar();
    } while (!fin);

    delete controlador;
    return 0;
}

#include "../lib/controlador.h"

Controlador* Controlador::instancia = nullptr; 

Controlador::Controlador() {
	this->pausa = false;
	this->nivel = 1;
    this->fin = false;

    this->moverArriba = false;
    this->moverAbajo = false;
    this->moverDerecha = false;
    this->moverIzquierda = false;
    this->mouseX = 0;

	for (int i = 0; i < this->largoTablero; ++i) {
		this->tablero[i] = new objeto * [anchoTablero];
		for (int j = 0; j < this->anchoTablero; j++) {
			this->tablero[i][j] = nullptr; 
		}
	}
}

Controlador::~Controlador() {};

Controlador* Controlador::getInstance() {
	if (instancia == nullptr) {
		instancia = new Controlador();
	}
	return instancia;
}


void Controlador::inicializar() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	window = SDL_CreateWindow("Bomberman-ICG",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	context = SDL_GL_CreateContext(window);

	glMatrixMode(GL_PROJECTION);

	glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 1.0f);

	gluPerspective(45, 1280 / 720.f, 1, 200);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}

void Controlador::manejarEventos() {
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
}

void Controlador::actualizar() {
	SDL_GL_SwapWindow(window);
}

void Controlador::dibujar() {

}

void Controlador::limpiar() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Controlador::getPausa() {
	return this->getPausa();
}

void Controlador::setPausa(bool pau) {
	this->pausa = pau;
}

bool Controlador::getNivel() {
	return this->nivel;
}

void Controlador::setNivel(int niv) {
	this->nivel = niv;
}

void Controlador::pausar() {
	this->pausa = !(this->pausa);
}

void Controlador::aumentarNivel() {
	this->nivel++;
}

bool Controlador::getFin() {
    return this->fin;
}

void Controlador::setFin(bool fin) {
    this->fin = fin;
}

bool Controlador::getMoverArriba() {
    return this->moverArriba;
}

bool Controlador::getMoverAbajo() {
    return this->moverAbajo;
}

bool Controlador::getMoverDerecha() {
    return this->moverDerecha;
}

bool Controlador::getMoverIzquierda() {
    return this->moverIzquierda;
}

void Controlador::setMoverArriba(bool moverArriba) {
    this->moverArriba = moverArriba;
}

void Controlador::setMoverDerecha(bool moverDerecha) {
    this->moverIzquierda = moverDerecha;
}

void Controlador::setMoverIzquierda(bool moverIzquierda) {
    this->moverIzquierda = moverIzquierda;
}

void Controlador::setMoverAbajo(bool moverAbajo) {
    this->moverAbajo = moverAbajo;
}

int Controlador::getMouseX() {
    return this->mouseX;
}

void Controlador::setMouseX(int mouseX) {
    this->mouseX = mouseX;
}




//crea la instancia de bomba, la asigna al arreglo de bombas en controlador, al del personaje que lo colocó y asigna el dueño a la bomba
void Controlador::crearBomba(int x, int z, personajes* pers) {
}

//ponerBomba lo que hace es obtener gracias a la matriz de objetos, si es valido poner una bomba en la posicion x, z. Y en caso de serlo crea la bomba
// si no, no hace nada
void Controlador::ponerBomba(int x, int z, personajes* pers) {
	if (pers->bombaDisponible() && this->tablero[x][z] == nullptr) {
		crearBomba(x, z, pers);
	}
}
#include "../lib/controlador.h"

Controlador* Controlador::instancia = nullptr; 

Controlador::Controlador() {
    this->global = global::getInstance();

    this->pausa = false;
    this->nivel = 1;
    this->fin = false;

    this->jugador = new bomberman(20, 20);

    for (int i = 0; i < this->largoTablero; ++i) {
        this->tablero[i] = new objeto * [anchoTablero];
        for (int j = 0; j < this->anchoTablero; j++) {
            this->tablero[i][j] = nullptr;
        }
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    this->window = SDL_CreateWindow("Bomberman-ICG",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    this->context = SDL_GL_CreateContext(window);

    glMatrixMode(GL_PROJECTION);

    glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 1.0f);

    gluPerspective(45, 1280 / 720.f, 1, 200);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
}

Controlador::~Controlador() {};

Controlador* Controlador::getInstance() {
	if (instancia == nullptr) {
		instancia = new Controlador();
	}
	return instancia;
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
                (*global).setMoverArriba(true);
                break;
            case SDLK_RIGHT:
                (*global).setMoverDerecha(true);
                break;
            case SDLK_DOWN:
                (*global).setMoverAbajo(true);
                break;
            case SDLK_LEFT:
                (*global).setMoverIzquierda(true);
                break;
            }
            break;
        case SDL_KEYUP:
            switch (evento.key.keysym.sym) {
            case SDLK_UP:
                (*global).setMoverArriba(false);
                break;
            case SDLK_RIGHT:
                (*global).setMoverDerecha(false);
                break;
            case SDLK_DOWN:
                (*global).setMoverAbajo(false);
                break;
            case SDLK_LEFT:
                (*global).setMoverIzquierda(false);
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            (*global).setMouseX(evento.motion.x % 360);
            break;
        }
    }
}

void Controlador::actualizar() {
    (*jugador).actualizar();
}

void Controlador::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    (*jugador).dibujar();


    glBegin(GL_QUADS);
    glColor3f(GLfloat(227.0 / 255.0), GLfloat(186.0 / 255.0), GLfloat(143.0 / 255.0));
    glVertex3f(20., 0., 20.);
    glVertex3f(20., 0., -20.);
    glVertex3f(-20., 0., -20.);
    glVertex3f(-20., 0., 20.);
    glEnd();

    SDL_GL_SwapWindow(window);

}

void Controlador::limpiar() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Controlador::getPausa() {
	return this->pausa;
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

//crea la instancia de bomba, la asigna al arreglo de bombas en controlador, al del personaje que lo colocó y asigna el dueño a la bomba
void Controlador::crearBomba(int x, int z, bomberman* pers) {
}

//ponerBomba lo que hace es obtener gracias a la matriz de objetos, si es valido poner una bomba en la posicion x, z. Y en caso de serlo crea la bomba
// si no, no hace nada
void Controlador::ponerBomba(int x, int z, bomberman* bomberman) {
	if (bomberman->bombaDisponible() && this->tablero[x][z] == nullptr) {
		crearBomba(x, z, bomberman);
	}
}
#include "../lib/controlador.h"

Controlador* Controlador::instancia = nullptr; 

Controlador::Controlador() {
    this->global = global::getInstance();

    //this->interfazJuego = interfazJuego::getInstance();
    this->ui = UI::getInstance();

    this->texturas_habilitadas = true;
    this->pausa = false;
    this->nivel = 1;
    this->fin = false;
    this->tiempoJuego = 200; //segundos
    this->puntaje = 0;

    this->jugador = new bomberman(0, 0, global->tile_size / 2, global->tile_size / 2, 2); //empieza en el (0,0)
 
    for (int i = 0; i < this->largoTablero; i++) {
        this->tablero[i] = new objeto *[anchoTablero];
    }
    for (int i = 0; i < this->largoTablero; i++) {
        for (int j = 0; j < this->anchoTablero; j++) {
            this->tablero[i][j] = nullptr;
        }
    }

    //crea el terreno (faltan los bordes del tablero)
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0); // Distribuci�n uniforme entre 0 y 1

    // Generar n�mero aleatorio entre 0 y 1
    double random_num;

    for (int i = 0; i < this->largoTablero; i++) {
        for (int j = 0; j < this->anchoTablero; j++) {
            if (((i % 2) == 1) && ((j % 2) == 1)) {
                this->tablero[i][j] = new estructura((GLfloat) i * global->tile_size, (GLfloat) j * global->tile_size, global->tile_size, global->tile_size, 2, false); //no destructible
            } else {
                random_num = dis(gen);
                if (random_num <= (*global).generadorTerreno) {
                    this->tablero[i][j] = new estructura((GLfloat) i * global->tile_size, (GLfloat) j * global->tile_size, global->tile_size, global->tile_size, 2,  true); //destructible
                }
            }
        }
    }

    //por ultimo elimino la esquina para que pueda hacer el primer movimiento sin morir explotado ni atacado
    if (this->tablero[0][0] != nullptr) {
        delete this->tablero[0][0];
    }
    this->tablero[0][0] = this->jugador;
    if (this->tablero[0][1] != nullptr) {
        delete this->tablero[0][1];
        this->tablero[0][1] = nullptr;
    }
    if (this->tablero[1][0] != nullptr) {
        delete this->tablero[1][0];
        this->tablero[1][0] = nullptr;
    }
    if (this->tablero[2][0] == nullptr) {
        this->tablero[2][0] = new estructura(2 * global->tile_size, 0, global->tile_size, global->tile_size, 2, true);
    }
    if (this->tablero[0][2] == nullptr) {
        this->tablero[0][2] = new estructura(0, 2 * global->tile_size, global->tile_size, global->tile_size, 2, true);
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    this->window = SDL_CreateWindow("Bomberman 3D",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        (*global).width, (*global).height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    this->context = SDL_GL_CreateContext(window);

    glMatrixMode(GL_PROJECTION);

    glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 1.0f);

    gluPerspective(45, GLfloat((*global).width) / GLfloat((*global).height), 1, 200);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);

    SDL_ShowCursor(SDL_DISABLE); // Esta línea oculta el cursor del mouse

    if (texturas_habilitadas)
        ControladorTexturas::cargarTexturas();
}

Controlador* Controlador::getInstance() {
	if (instancia == nullptr) 
		instancia = new Controlador();

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
                    (*global).moverArriba = true;
                    break;
                case SDLK_RIGHT:
                    (*global).moverDerecha = true;
                    break;
                case SDLK_DOWN:
                    (*global).moverAbajo = true;
                    break;
                case SDLK_LEFT:
                    (*global).moverIzquierda = true;
                    break;
                /*case SDLK_h:
                    (*interfazJuego).swapVisible();
                    break;*/
            }
            break;
        case SDL_KEYUP:
            switch (evento.key.keysym.sym) {
                case SDLK_UP:
                    (*global).moverArriba = false;
                    break;
                case SDLK_RIGHT:
                    (*global).moverDerecha = false;
                    break;
                case SDLK_DOWN:
                    (*global).moverAbajo = false;
                    break;
                case SDLK_LEFT:
                    (*global).moverIzquierda = false;
                    break;
            }
            break;
        case SDL_MOUSEMOTION:
            (*global).mouseX = ((*global).mouseX + (evento.motion.x % 360) - 280) % 360; //No hardcodear el 280 (kevin machado)
            if ((*global).mouseX < 0)
                (*global).mouseX += 360;                       

            SDL_WarpMouseInWindow(window, global->width / 2, global->height / 2);
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

    //Colocacion de camara
    GLfloat angleRadians = (*global).mouseX * (3.14159f / 180.0f); 

    GLfloat camX = (*jugador).getCoordX() + 20.0f * sin(angleRadians);
    GLfloat camZ = (*jugador).getCoordZ() + 20.0f * cos(angleRadians);

    gluLookAt(camX, 30, camZ, (*jugador).getCoordX(), 0, (*jugador).getCoordZ(), 0, 1, 0);
    //Fin de colocacion de camara

    (*jugador).dibujar();

    ui->draw();

    if (texturas_habilitadas) 
        glEnable(GL_TEXTURE_2D);

    for (int i = 0; i < this->largoTablero; i++) {
        for (int j = 0; j < this->anchoTablero; j++) {
            if (this->tablero[i][j] != nullptr && (this->tablero[i][j] != this->jugador)) {
                this->tablero[i][j]->dibujar();
            }       
        }
    }

    if (texturas_habilitadas) 
        glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glColor3f(GLfloat(227.0 / 255.0), GLfloat(186.0 / 255.0), GLfloat(143.0 / 255.0));
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, anchoTablero * global->tile_size);
    glVertex3f(largoTablero * global->tile_size, 0, anchoTablero * global->tile_size);
    glVertex3f(largoTablero * global->tile_size, 0, 0);
    glEnd();

    SDL_GL_SwapWindow(window);
}

Controlador::~Controlador() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

SDL_Window* Controlador::getWindow() {
    return this->window;
}

bool Controlador::getTexturasHabilitadas() {
    return this->texturas_habilitadas;
}

void Controlador::setTexturasHabilitadas(bool text) {
    this->texturas_habilitadas = text;
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

void Controlador::toggle_pausa() {
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

int Controlador::getLargoTablero() {
    return this->largoTablero;
}
void Controlador::setLargoTablero(int largo) {
    this->largoTablero = largo;
}

int Controlador::getAnchoTablero() {
    return this->anchoTablero;
}

void Controlador::setAnchoTablero(int ancho) {
    this->anchoTablero = ancho;
}

bomberman* Controlador::getBomberman() {
    return this->jugador;
}

void Controlador::aumentarPuntaje(int punt) {
    this->puntaje += punt;
}

objeto*** Controlador::getTablero() {
    return this->tablero;
}

//ponerBomba lo que hace es obtener gracias a la matriz de objetos, si es valido poner una bomba en la posicion x, z. Y en caso de serlo crea la bomba
// si no, no hace nada
void Controlador::ponerBomba(int x, int z) {
	if (jugador->bombaDisponible() && this->tablero[x][z] == nullptr) {
        //Validar si es posible colocar bomba, y hacerlo en caso de ser posible
	}
}

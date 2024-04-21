#include "../lib/controlador.h"

Controlador* Controlador::instancia = nullptr; 

Controlador::Controlador() {
    texturas_habilitadas = true;
    pausa = false;
    nivel = 1;
    fin = false;
    tiempoJuego = 200; //segundos
    puntaje = 0;

    jugador = new bomberman({ 0, 0, 0 }, { tile_size / 2, tile_size / 2, tile_size / 2 }, GLfloat(0.1));

    for (int i = 0; i < largoTablero; i++) {
        estructuras[i] = new objeto * [anchoTablero];
        bombas[i] = new objeto * [anchoTablero];
        fuegos[i] = new objeto * [anchoTablero];
        enemigos[i] = new objeto * [anchoTablero];
    }

    for (int i = 0; i < largoTablero; i++){
        for (int j = 0; j < anchoTablero; j++) {
            estructuras[i][j] = nullptr;
            bombas[i][j] = nullptr;
            fuegos[i][j] = nullptr;
            enemigos[i][j] = nullptr;
        }
    }

    //crea el terreno (faltan los bordes del tablero)
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0); // Distribuci�n uniforme entre 0 y 1

    // Generar n�mero aleatorio entre 0 y 1
    double random_num;

    for (int i = 0; i < largoTablero; i++) {
        for (int j = 0; j < anchoTablero; j++) {
            if (((i % 2) == 1) && ((j % 2) == 1)) {
                estructuras[i][j] = new estructura({ (GLfloat)i * tile_size, 0, (GLfloat)j * tile_size }, { tile_size, tile_size, tile_size }, false); //no destructible
            } else {
                random_num = dis(gen);
                if (random_num <= generadorTerreno) {
                    estructuras[i][j] = new estructura({ (GLfloat)i * tile_size, 0, (GLfloat)j * tile_size }, { tile_size, tile_size, tile_size }, true); //destructible
                }
            }
        }
    }

    //por ultimo elimino la esquina para que pueda hacer el primer movimiento sin morir explotado ni atacado
    if (estructuras[0][0] != nullptr) {
        delete estructuras[0][0];
        estructuras[0][0] = nullptr;
    }
    if (estructuras[0][1] != nullptr) {
        delete estructuras[0][1];
        estructuras[0][1] = nullptr;
    }
    if (estructuras[1][0] != nullptr) {
        delete estructuras[1][0];
        estructuras[1][0] = nullptr;
    }
    if (estructuras[2][0] == nullptr) {
        estructuras[2][0] = new estructura({ 2 * tile_size, 0, 0 }, { tile_size, tile_size, tile_size }, true);
    }
    if (estructuras[0][2] == nullptr) {
        estructuras[0][2] = new estructura({ 0, 0, 2 * tile_size }, { tile_size, tile_size, tile_size }, true);
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    this->window = SDL_CreateWindow("Bomberman 3D",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    this->context = SDL_GL_CreateContext(window);

    glMatrixMode(GL_PROJECTION);

    glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 1.0f);

    gluPerspective(45, GLfloat(WINDOW_WIDTH) / GLfloat(WINDOW_HEIGHT), 1, 200);
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

int posBombaXTablero, posBombaZTablero;
void Controlador::manejarEventos() {
    while (SDL_PollEvent(&evento)) {
        switch (evento.type) {
            case SDL_QUIT:
                fin = true;
                break;
        case SDL_KEYDOWN:
            switch (evento.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    fin = true;
                    break;
                case SDLK_b:
                    if (mouseX >= 45 && mouseX < 135){
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x - tile_size, 1);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z, 1);
                    }
                    if (mouseX >= 135 && mouseX < 225) {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x, 1);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z + tile_size, 1);
                    }
                    if (mouseX >= 225 && mouseX < 315) {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x + tile_size, 1);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z, 1);
                    }
                    if (mouseX >= 315 || mouseX < 45) {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x, 1);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z - tile_size, 1);
                    }

                    if (bombas[posBombaXTablero][posBombaZTablero] == nullptr) {
                        objeto* bomba_obj = new bomba({ posBombaXTablero * tile_size + GLfloat(0.5), 0, posBombaZTablero * tile_size + GLfloat(0.5) },
                            { tile_size / 2, tile_size / 2, tile_size / 2},
                            2000,
                            2
                        );

                        bombas[posBombaXTablero][posBombaZTablero] = bomba_obj;
                    }
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
            mouseX = (mouseX + (evento.motion.x % 360) - 280) % 360; //No hardcodear el 280 (kevin machado)
            if (mouseX < 0)
                mouseX += 360;                       

            SDL_WarpMouseInWindow(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
            break;
        }
    }
}

void Controlador::actualizar() { 
    jugador->actualizar();

    for (int i = 0; i < largoTablero; i++) {
        for (int j = 0; j < anchoTablero; j++) {
            if (estructuras[i][j] != nullptr)
                estructuras[i][j]->actualizar();

            if (bombas[i][j] != nullptr)
                bombas[i][j]->actualizar();

            if (fuegos[i][j] != nullptr)
                fuegos[i][j]->actualizar();

            if (enemigos[i][j] != nullptr)
                enemigos[i][j]->actualizar();

        }
    }
}

void Controlador::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //Colocacion de camara
    GLfloat angleRadians = mouseX * (3.14159f / 180.0f); 

    GLfloat camX = (*jugador).getPosicion().x + 20.0f * sin(angleRadians);
    GLfloat camZ = (*jugador).getPosicion().z + 20.0f * cos(angleRadians);

    gluLookAt(camX, 30, camZ, (*jugador).getPosicion().x, 0, (*jugador).getPosicion().z, 0, 1, 0);
    //Fin de colocacion de camara

    if (texturas_habilitadas) 
        glEnable(GL_TEXTURE_2D);

    jugador->dibujar();

    for (int i = 0; i < largoTablero; i++) {
        for (int j = 0; j < anchoTablero; j++) {
            if (estructuras[i][j] != nullptr)
                estructuras[i][j]->dibujar();

            if (bombas[i][j] != nullptr)
                bombas[i][j]->dibujar();

            if (fuegos[i][j] != nullptr)
                fuegos[i][j]->dibujar();

            if (enemigos[i][j] != nullptr)
                enemigos[i][j]->dibujar();

        }
    }

    if (texturas_habilitadas) 
        glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glColor3f(GLfloat(227.0 / 255.0), GLfloat(186.0 / 255.0), GLfloat(143.0 / 255.0));
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, anchoTablero * tile_size);
    glVertex3f(largoTablero * tile_size, 0, anchoTablero * tile_size);
    glVertex3f(largoTablero * tile_size, 0, 0);
    glEnd();

    SDL_GL_SwapWindow(window);
}

Controlador::~Controlador() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

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

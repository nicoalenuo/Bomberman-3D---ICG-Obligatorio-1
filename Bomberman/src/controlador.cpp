#include "../lib/controlador.h"

Controlador* Controlador::instancia = nullptr; 

Controlador::Controlador() {
    nivel = 1;
    fin = false;
    finJuego = false;
    pausa = false;
    tiempoJuego = 200; //segundos
    puntaje = 0;

    jugador = new bomberman(
        { tile_size / 2, 0, tile_size / 2 },
        { tile_size / 4, tile_size / 2, tile_size / 4 }, 
        GLfloat(0.1)
    );

    for (int i = 0; i < largoTablero; i++) {
        estructuras[i] = new objeto * [anchoTablero];
        bombas[i] = new objeto * [anchoTablero];
        fuegos[i] = new objeto * [anchoTablero];
        enemigos[i] = new objeto * [anchoTablero];
        bonificadores[i] = new objeto * [anchoTablero];
    }

    for (int i = 0; i < largoTablero; i++){
        for (int j = 0; j < anchoTablero; j++) {
            estructuras[i][j] = nullptr;
            bombas[i][j] = nullptr;
            fuegos[i][j] = nullptr;
            enemigos[i][j] = nullptr;
            bonificadores[i][j] = nullptr;
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
                estructuras[i][j] = new estructura(
                    { (GLfloat)i * tile_size + tile_size / 2, 0, (GLfloat)j * tile_size + tile_size / 2 },
                    { tile_size / 2, tile_size, tile_size / 2 }, 
                      false
                ); //no destructible
            } else {
                random_num = dis(gen);
                if (random_num <= generadorTerreno) {
                    estructuras[i][j] = new estructura(
                        { (GLfloat)i * tile_size + tile_size / 2, 0, (GLfloat)j * tile_size + tile_size / 2 },
                        { tile_size / 2, tile_size, tile_size / 2 },
                          true
                    ); //destructible
                }
                else if (random_num <= generadorBonificador + generadorTerreno) {
                    bonificadores[i][j] = new bonificador(
                        { (GLfloat)i * tile_size + tile_size / 2, tile_size / 2, (GLfloat)j * tile_size + tile_size / 2 },
                        { 0.1f, 0.7f, 0.1f },
                        BONIFICADOR_RANDOM
                    );
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
        estructuras[2][0] = new estructura(
            { 2 * tile_size + tile_size / 2, 0, tile_size / 2 }, 
            { tile_size / 2, tile_size, tile_size / 2}, 
              true);
    }
    if (estructuras[0][2] == nullptr) {
        estructuras[0][2] = new estructura(
            { tile_size / 2, 0, 2 * tile_size + tile_size / 2 }, 
            { tile_size / 2, tile_size, tile_size / 2}, 
              true);
    }

    if (bonificadores[0][0] != nullptr) {
        delete bonificadores[0][0];
        bonificadores[0][0] = nullptr;
    }
    if (bonificadores[0][1] != nullptr) {
        delete bonificadores[0][1];
        bonificadores[0][1] = nullptr;
    }
    if (bonificadores[1][0] != nullptr) {
        delete bonificadores[1][0];
        bonificadores[1][0] = nullptr;
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

    glClearColor(0.52f, 0.80f, 0.92f, 1.0f);

    gluPerspective(45, GLfloat(WINDOW_WIDTH) / GLfloat(WINDOW_HEIGHT), 1, 200);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);

    SDL_ShowCursor(SDL_DISABLE); // Esta línea oculta el cursor del mouse


    ControladorTexturas::cargarTexturas();
    ControladorObjetos::cargarObjetos();
    ControladorInterfaz::cargarInterfaz(puntaje, tiempoJuego, fin);
}

Controlador* Controlador::getInstance() {
	if (instancia == nullptr) 
		instancia = new Controlador();

	return instancia;
}

int posBombaXTablero, posBombaZTablero, mouseYNuevo;
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
                    if (mouseX >= 45 && mouseX < 135) {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x - tile_size);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z);
                    }
                    else if (mouseX >= 135 && mouseX < 225) {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z + tile_size);
                    }
                    else if (mouseX >= 225 && mouseX < 315) {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x + tile_size);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z);
                    }
                    else {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z - tile_size);
                    }


                    if (posBombaXTablero >= 0 && posBombaXTablero < largoTablero &&
                        posBombaZTablero >= 0 && posBombaZTablero < anchoTablero &&
                        bombas[posBombaXTablero][posBombaZTablero] == nullptr &&
                        estructuras[posBombaXTablero][posBombaZTablero] == nullptr) {

                        objeto* bomba_obj = new bomba(
                            { posBombaXTablero * tile_size + tile_size / 2, 0, posBombaZTablero * tile_size + tile_size / 2 },
                            { tile_size / 4, tile_size / 2, tile_size / 4 },
                            2000, //2 segundos
                            2
                        );
                        bombas[posBombaXTablero][posBombaZTablero] = bomba_obj;
                    }
                    break;
                case SDLK_v:
                        ControladorCamara::cambiarTipoCamara();
                    break;
                case SDLK_p:
                    toggle_pausa();
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

            mouseX = (mouseX - (evento.motion.x - (WINDOW_WIDTH / 2))) % 360;
            if (mouseX < 0)
                mouseX += 360;

            mouseY= mouseY + (evento.motion.y - (WINDOW_HEIGHT/2));
            if (mouseY < 1)
                mouseY = 1;
            else if (mouseY > 90)
                mouseY = 90;

            SDL_WarpMouseInWindow(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            switch (evento.button.button) {
                case SDL_BUTTON_LEFT:
                    if (mouseX >= 45 && mouseX < 135) {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x - tile_size);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z);
                    }
                    else if (mouseX >= 135 && mouseX < 225) {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z + tile_size);
                    }
                    else if (mouseX >= 225 && mouseX < 315) {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x + tile_size);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z);
                    }
                    else {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z - tile_size);
                    }

                    
                    if (posBombaXTablero >= 0 && posBombaXTablero < largoTablero &&
                        posBombaZTablero >= 0 && posBombaZTablero < anchoTablero &&
                        bombas[posBombaXTablero][posBombaZTablero] == nullptr && 
                        estructuras[posBombaXTablero][posBombaZTablero] == nullptr) {

                        objeto* bomba_obj = new bomba(
                            { posBombaXTablero * tile_size + tile_size / 2, 0, posBombaZTablero * tile_size + tile_size / 2 },
                            { tile_size / 4, tile_size / 2, tile_size / 4 },
                            2000, //2 segundos
                            2
                        );
                        bombas[posBombaXTablero][posBombaZTablero] = bomba_obj;
                    }
                break;
            }
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

            if (bonificadores[i][j] != nullptr)
                bonificadores[i][j]->actualizar();

        }
    }

    for (list<particula*>::iterator it = particulas.begin(); it != particulas.end(); ++it)
        (*it)->actualizar();

    for (list<particula*>::iterator it = particulas.begin(); it != particulas.end();){
        if ((*it)->getEliminar()) {
            delete (*it);
            it = particulas.erase(it);
        }
        else 
            ++it;
    }
    
    ControladorInterfaz::setPuntaje(puntaje);
    ControladorInterfaz::setTiempo(tiempoJuego);
    ControladorInterfaz::setFinJuego(finJuego);
}

void Controlador::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    ControladorCamara::colocarCamara();

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

            if (bonificadores[i][j] != nullptr)
                bonificadores[i][j]->dibujar();
        }
    }

    for (auto it = particulas.begin(); it != particulas.end(); ++it)
        (*it)->dibujar();

    //Suelo
    glColor3f(0.75f, 0.63f, 0.50f);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, anchoTablero * tile_size);
    glVertex3f(largoTablero * tile_size, 0, anchoTablero * tile_size);
    glVertex3f(largoTablero * tile_size, 0, 0);
    glEnd();
    
    ControladorInterfaz::dibujarHUD();

    SDL_GL_SwapWindow(window);
}

Controlador::~Controlador() {
    
    for (int i = 0; i < largoTablero; i++) {
        for (int j = 0; j < anchoTablero; j++) {
            if (estructuras[i][j] != nullptr)
                delete estructuras[i][j];

            if (bombas[i][j] != nullptr)
                delete bombas[i][j];

            if (fuegos[i][j] != nullptr)
                delete fuegos[i][j];

            if (enemigos[i][j] != nullptr)
                delete enemigos[i][j];

            if (bonificadores[i][j] != nullptr)
                delete bonificadores[i][j];

        }
    }

    for (list<particula*>::iterator it = particulas.begin(); it != particulas.end();) {
        delete (*it);
        it = particulas.erase(it);
        ++it;
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

void Controlador::sumarPuntaje(int puntos) {
    this->puntaje += puntos;
    if (puntos > INT_MAX) {
        puntos = INT_MAX;
        this->fin = true;
    }
}

void Controlador::disminuirTiempo(int segundos) {
    this->tiempoJuego -= segundos;
    if (this->tiempoJuego <= 0) {
        tiempoJuego = 0;
        this->finJuego = true;
    }
}
#include "../lib/controlador.h"

Controlador* Controlador::instancia = nullptr; 

Controlador::Controlador() {
    global = global::getInstance();

    texturas_habilitadas = true;
    pausa = false;
    nivel = 1;
    fin = false;
    tiempoJuego = 200; //segundos
    puntaje = 0;

    jugador = new bomberman({ 0, 0, 0 }, { tile_size / 2, tile_size / 2, tile_size / 2 });

    for (int i = 0; i < this->largoTablero; i++) {
        estructuras[i] = new objeto * [anchoTablero];
        bombas[i] = new objeto * [anchoTablero];
        fuegos[i] = new objeto * [anchoTablero];
        enemigos[i] = new objeto * [anchoTablero];
    }

    for (int i = 0; i < this->largoTablero; i++){
        for (int j = 0; j < this->anchoTablero; j++) {
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

    for (int i = 0; i < this->largoTablero; i++) {
        for (int j = 0; j < this->anchoTablero; j++) {
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

int posBombaXTablero, posBombaZTablero, mouseX;
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
                    mouseX = (*global).mouseX;

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
                            { 1, 1, 1 },
                            2000,
                            2
                        );

                        bombas[posBombaXTablero][posBombaZTablero] = bomba_obj;
                    }
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

            SDL_WarpMouseInWindow(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
            break;
        }
    }
}

void Controlador::actualizar() { 
    jugador->actualizar();

    for (int i = 0; i < this->largoTablero; i++) {
        for (int j = 0; j < this->anchoTablero; j++) {
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
    GLfloat angleRadians = (*global).mouseX * (3.14159f / 180.0f); 

    GLfloat camX = (*jugador).getPosicion().x + 20.0f * sin(angleRadians);
    GLfloat camZ = (*jugador).getPosicion().z + 20.0f * cos(angleRadians);

    gluLookAt(camX, 30, camZ, (*jugador).getPosicion().x, 0, (*jugador).getPosicion().z, 0, 1, 0);
    //Fin de colocacion de camara

    if (texturas_habilitadas) 
        glEnable(GL_TEXTURE_2D);

    jugador->dibujar();

    for (int i = 0; i < this->largoTablero; i++) {
        for (int j = 0; j < this->anchoTablero; j++) {
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

objeto*** Controlador::getEstructuras() { return estructuras; }

objeto*** Controlador::getEnemigos() { return enemigos; }

objeto*** Controlador::getBombas() { return bombas; }

objeto*** Controlador::getFuegos() { return fuegos; }

bool Controlador::posicion_valida(posicion pos, tamanio tam) {
    int largoTableroAux = largoTablero * tile_size;
    int anchoTableroAux = anchoTablero * tile_size;

    objeto* obj_1 = estructuras[int(pos.x) / int(tile_size)][int(pos.z) / int(tile_size)];
    objeto* obj_2 = estructuras[int(pos.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];
    objeto* obj_3 = estructuras[int(pos.x + tam.x) / int(tile_size)][int(pos.z) / int(tile_size)];
    objeto* obj_4 = estructuras[int(pos.x + tam.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];

    objeto* obj_5 = bombas[int(pos.x) / int(tile_size)][int(pos.z) / int(tile_size)];
    objeto* obj_6 = bombas[int(pos.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];
    objeto* obj_7 = bombas[int(pos.x + tam.x) / int(tile_size)][int(pos.z) / int(tile_size)];
    objeto* obj_8 = bombas[int(pos.x + tam.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];

    return
        pos.x >= 0 &&
        pos.x + tam.x <= largoTableroAux &&
        pos.z >= 0 &&
        pos.z + tam.z <= anchoTableroAux &&
        (obj_1 == nullptr || pos.x < obj_1->getPosicion().x || pos.x > obj_1->getPosicion().x + obj_1->getTamanio().x || pos.z < obj_1->getPosicion().z || pos.z > obj_1->getPosicion().z + obj_1->getTamanio().z) &&
        (obj_2 == nullptr || pos.x < obj_2->getPosicion().x || pos.x > obj_2->getPosicion().x + obj_2->getTamanio().x || pos.z + tam.z < obj_2->getPosicion().z || pos.z + tam.z > obj_2->getPosicion().z + obj_2->getTamanio().z) &&
        (obj_3 == nullptr || pos.x + tam.x < obj_3->getPosicion().x || pos.x + tam.x > obj_3->getPosicion().x + obj_3->getTamanio().x || pos.z < obj_3->getPosicion().z || pos.z > obj_3->getPosicion().z + obj_3->getTamanio().z) &&
        (obj_4 == nullptr || pos.x + tam.x < obj_4->getPosicion().x || pos.x + tam.x > obj_4->getPosicion().x + obj_4->getTamanio().x || pos.z + tam.z < obj_4->getPosicion().z || pos.z + tam.z > obj_4->getPosicion().z + obj_4->getTamanio().z) &&
        (obj_5 == nullptr || pos.x < obj_5->getPosicion().x || pos.x > obj_5->getPosicion().x + obj_5->getTamanio().x || pos.z < obj_5->getPosicion().z || pos.z > obj_5->getPosicion().z + obj_5->getTamanio().z) &&
        (obj_6 == nullptr || pos.x < obj_6->getPosicion().x || pos.x > obj_6->getPosicion().x + obj_6->getTamanio().x || pos.z + tam.z < obj_6->getPosicion().z || pos.z + tam.z > obj_6->getPosicion().z + obj_6->getTamanio().z) &&
        (obj_7 == nullptr || pos.x + tam.x < obj_7->getPosicion().x || pos.x + tam.x > obj_7->getPosicion().x + obj_7->getTamanio().x || pos.z < obj_7->getPosicion().z || pos.z > obj_7->getPosicion().z + obj_7->getTamanio().z) &&
        (obj_8 == nullptr || pos.x + tam.x < obj_8->getPosicion().x || pos.x + tam.x > obj_8->getPosicion().x + obj_8->getTamanio().x || pos.z + tam.z < obj_8->getPosicion().z || pos.z + tam.z > obj_8->getPosicion().z + obj_8->getTamanio().z);
}

//Devuelve la posicion en x dentro del tablero de un objeto
int Controlador::getPosicionXEnTablero(GLfloat coord_x, GLfloat ancho_x) {
    return int(coord_x + (ancho_x / 2)) / int(tile_size);
}

int Controlador::getPosicionZEnTablero(GLfloat coord_z, GLfloat ancho_z) {
    return int(coord_z + (ancho_z / 2)) / int(tile_size);
}
#include "../lib/controlador.h"
#include <random>
#include "FreeImage.h"

Controlador* Controlador::instancia = nullptr; 

Controlador::Controlador() {
    this->global = global::getInstance();

    this->textura = true;
    this->pausa = false;
    this->nivel = 1;
    this->fin = false;
    this->tiempoJuego = 200; //segundos
    this->puntaje = 0;

    this->jugador = new bomberman(0, 0); //empieza en el (0,0)
 
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
                this->tablero[i][j] = new estructura((float) i, (float) j, false); //no destructible
            } else {
                random_num = dis(gen);
                if (random_num <= (*global).generadorTerreno) {
                    this->tablero[i][j] = new estructura((float) i, (float) j, true); //destructible
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
        this->tablero[2][0] = new estructura(2, 0, true);
    }
    if (this->tablero[0][2] == nullptr) {
        this->tablero[0][2] = new estructura(0, 2, true);
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    this->window = SDL_CreateWindow("Bomberman 3D",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    this->context = SDL_GL_CreateContext(window);

    glMatrixMode(GL_PROJECTION);

    glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 1.0f);

    gluPerspective(45, 1280 / 720.f, 1, 200);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);

    //SDL_ShowCursor(SDL_DISABLE); // Esta línea oculta el cursor del mouse

    this->cargarTextura();
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
            (*global).mouseX = (evento.motion.x % 360);
            break;
        }
    }
}

void Controlador::actualizar() { //faltan actualizar las bombas
    (*jugador).actualizar();
}

void Controlador::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    (*jugador).dibujar();

    bool textura = this->textura;

    if (textura) {
        glEnable(GL_TEXTURE_2D);
    }

    for (int i = 0; i < this->largoTablero; i++) {
        for (int j = 0; j < this->anchoTablero; j++) {
            if (this->tablero[i][j] != nullptr && (this->tablero[i][j] != this->jugador)) {
                this->tablero[i][j]->dibujar();
            }       
        }
    }

    if (textura) {
        glDisable(GL_TEXTURE_2D);
    }

    glBegin(GL_QUADS);
    glColor3f(GLfloat(227.0 / 255.0), GLfloat(186.0 / 255.0), GLfloat(143.0 / 255.0));
    global::getInstance();
    GLfloat largoMedio = (this->largoTablero * global->largoEstructura) / 2;
    GLfloat anchoMedio = (this->anchoTablero * global->largoEstructura) / 2;

    glVertex3f(largoMedio, 0., anchoMedio);
    glVertex3f(largoMedio, 0., -anchoMedio);
    glVertex3f(-largoMedio, 0., -anchoMedio);
    glVertex3f(-largoMedio, 0., anchoMedio);
    glEnd();

    SDL_GL_SwapWindow(window);

}

void Controlador::limpiar() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window* Controlador::getWindow() {
    return this->window;
}

void Controlador::cargarTextura(){
    bool textura = this->getTextura();

    if (textura) {
        //TEXTURA
        char* archivo1 = new char[20];
        archivo1 = "../Bomberman/texturas/estructuraTrue.jpg"; //sacar
        //CARGAR IMAGEN
        FREE_IMAGE_FORMAT fif1 = FreeImage_GetFIFFromFilename(archivo1);
        FIBITMAP* bitmap1 = FreeImage_Load(fif1, archivo1); //estoy recibiendo bitmap null
        bitmap1 = FreeImage_ConvertTo24Bits(bitmap1);
        int w1 = FreeImage_GetWidth(bitmap1);
        int h1 = FreeImage_GetHeight(bitmap1);
        void* datos1 = FreeImage_GetBits(bitmap1);
        //FIN CARGAR IMAGEN

        GLuint textura1;
        glGenTextures(1, &textura1);
        glBindTexture(GL_TEXTURE_2D, textura1);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w1, h1, 0, GL_BGR, GL_UNSIGNED_BYTE, datos1);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        //FIN TEXTURA

        this->textura1 = textura1;

        //TEXTURA
        char* archivo2 = new char[20];
        archivo2 = "../Bomberman/texturas/estructuraFalse.png"; //sacar

        //CARGAR IMAGEN
        FREE_IMAGE_FORMAT fif2 = FreeImage_GetFIFFromFilename(archivo2);
        FIBITMAP* bitmap2 = FreeImage_Load(fif2, archivo2); //estoy reciviendo bitmap null
        bitmap2 = FreeImage_ConvertTo24Bits(bitmap2);
        int w2 = FreeImage_GetWidth(bitmap2);
        int h2 = FreeImage_GetHeight(bitmap2);
        void* datos2 = FreeImage_GetBits(bitmap2);
        //FIN CARGAR IMAGEN

        GLuint textura2;
        glGenTextures(1, &textura2);
        glBindTexture(GL_TEXTURE_2D, textura2);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w2, h2, 0, GL_BGR, GL_UNSIGNED_BYTE, datos2);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        this->textura2 = textura2;
        //FIN TEXTURA
    }
}

bool Controlador::getTextura() {
    return this->textura;
}

void Controlador::setTextura(bool text) {
    this->textura = text;
}

GLuint Controlador::getTextura1() {
    return this->textura1;
}
void Controlador::setTextura1(GLuint text) {
    this->textura1 = text;
}

GLuint Controlador::getTextura2() {
    return this->textura2;
}

void Controlador::setTextura2(GLuint text) {
    this->textura2 = text;
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

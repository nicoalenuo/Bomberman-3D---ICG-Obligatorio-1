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
                this->tablero[i][j] = new estructura(i,j,false); //no destructible
            } else {
                random_num = dis(gen);
                if (random_num <= (*global).generadorTerreno) {
                    this->tablero[i][j] = new estructura(i, j, true); //destructible
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
            (*global).mouseX = evento.motion.x % 360; //cambiar esto pq gira a todo trapo
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

    bool textura = this->textura;

    if (textura) {
        glEnable(GL_TEXTURE_2D);
    }

    for (int i = 0; i < this->largoTablero; i++) {
        for (int j = 0; j < this->anchoTablero; j++) {
            if (this->tablero[i][j] != nullptr && (this->tablero[i][j] != this->jugador)) {
                
                if (textura) {
                    estructura* est = dynamic_cast<estructura*>(this->tablero[i][j]);
                    if (est->getDestructible()) {
                        glBindTexture(GL_TEXTURE_2D, this->textura1);
                    } else {
                        glBindTexture(GL_TEXTURE_2D, this->textura2);
                    }
                        
                }

                GLfloat xReal = (i - 14.5) * global->largoEstructura;
                GLfloat zReal = (j - 5.5) * global->largoEstructura;

                glBegin(GL_QUADS);
                glColor3f(1.0, 1.0, 1.0);
                // Cara frontal (z = 1/2)
                if (textura) {
                    glTexCoord2f(0, 0);
                }
                glVertex3f(xReal, 0, zReal + global->largoEstructura);
                if (textura) {
                    glTexCoord2f(0, 1);
                }
                glVertex3f(xReal + global->largoEstructura, 0, zReal + global->largoEstructura);
                if (textura) {
                    glTexCoord2f(1, 1);
                }
                glVertex3f(xReal + global->largoEstructura, global->largoEstructura, zReal + global->largoEstructura);
                if (textura) {
                    glTexCoord2f(1, 0);
                }
                glVertex3f(xReal, global->largoEstructura, zReal + global->largoEstructura);

                // Cara posterior (z = -1/2)
                glColor3f(1.0, 1.0, 1.0);
                if (textura) {
                    glTexCoord2f(0, 0);
                }
                glVertex3f(xReal, 0, zReal);
                if (textura) {
                    glTexCoord2f(0, 1);
                }
                glVertex3f(xReal + global->largoEstructura, 0, zReal);
                if (textura) {
                    glTexCoord2f(1, 1);
                }
                glVertex3f(xReal + global->largoEstructura, global->largoEstructura, zReal);
                if (textura) {
                    glTexCoord2f(1, 0);
                }
                glVertex3f(xReal, global->largoEstructura, zReal);

                // Cara superior (y = 1/2)
                glColor3f(1.0, 1.0, 1.0);
                if (textura) {
                    glTexCoord2f(0, 0);
                }
                glVertex3f(xReal, global->largoEstructura, zReal);
                if (textura) {
                    glTexCoord2f(0, 1);
                }
                glVertex3f(xReal + global->largoEstructura, global->largoEstructura, zReal);
                if (textura) {
                    glTexCoord2f(1, 1);
                }
                glVertex3f(xReal + global->largoEstructura, global->largoEstructura, zReal + global->largoEstructura);
                if (textura) {
                    glTexCoord2f(1, 0);
                }
                glVertex3f(xReal, global->largoEstructura, zReal + global->largoEstructura);

                // Cara inferior (y = -1/2)
                glColor3f(1.0, 1.0, 1.0);
                if (textura) {
                    glTexCoord2f(0, 0);
                }
                glVertex3f(xReal, 0, zReal);
                if (textura) {
                    glTexCoord2f(0, 1);
                }
                glVertex3f(xReal + global->largoEstructura, 0, zReal);
                if (textura) {
                    glTexCoord2f(1, 1);
                }
                glVertex3f(xReal + global->largoEstructura, 0, zReal + global->largoEstructura);
                if (textura) {
                    glTexCoord2f(1, 0);
                }
                glVertex3f(xReal, 0, zReal + global->largoEstructura);

                // Cara izquierda (x = -1/2)
                glColor3f(1.0, 1.0, 1.0);
                if (textura) {
                    glTexCoord2f(0, 0);
                }
                glVertex3f(xReal, 0, zReal);
                if (textura) {
                    glTexCoord2f(0, 1);
                }
                glVertex3f(xReal, 0, zReal + global->largoEstructura);
                if (textura) {
                    glTexCoord2f(1, 1);
                }
                glVertex3f(xReal, global->largoEstructura, zReal + global->largoEstructura);
                if (textura) {
                    glTexCoord2f(1, 0);
                }
                glVertex3f(xReal, global->largoEstructura, zReal);

                // Cara derecha (x = 1/2)
                glColor3f(1.0, 1.0, 1.0);
                if (textura) {
                    glTexCoord2f(0, 0);
                }
                glVertex3f(xReal + global->largoEstructura, 0, zReal);
                if (textura) {
                    glTexCoord2f(0, 1);
                }
                glVertex3f(xReal + global->largoEstructura, 0, zReal + global->largoEstructura);
                if (textura) {
                    glTexCoord2f(1, 1);
                }
                glVertex3f(xReal + global->largoEstructura, global->largoEstructura, zReal + global->largoEstructura);
                if (textura) {
                    glTexCoord2f(1, 0);
                }
                glVertex3f(xReal + global->largoEstructura, global->largoEstructura, zReal);
                glEnd();
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

void Controlador::cargarTextura(){
    bool textura = this->getTextura();

    if (textura) {
        //TEXTURA
        char* archivo1 = new char[20];
        archivo1 = "../Bomberman/texturas/estT.jpg"; //sacar
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
        archivo2 = "../Bomberman/texturas/estF.png"; //sacar

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

//crea la instancia de bomba, la asigna al arreglo de bombas en controlador, al del personaje que lo coloc� y asigna el due�o a la bomba
void Controlador::crearBomba(int x, int z, personaje* pers) {
    /*
    bomba* bomb = new bomba(x, z, pers->getTiempoBomba(), pers->getLargoBomba());
    global::insertarBomba(this->bombas, bomb);
    bomb->setJugador(pers);
    global::insertarBomba(pers->getBomba(), bomb);
    */
}

//ponerBomba lo que hace es obtener gracias a la matriz de objetos, si es valido poner una bomba en la posicion x, z. Y en caso de serlo crea la bomba
// si no, no hace nada
void Controlador::ponerBomba(int x, int z, personaje* pers) {
	if (pers->bombaDisponible() && this->tablero[x][z] == nullptr) {
		crearBomba(x, z, pers);
	}
}

void Controlador::explotarBomba(bomba* bomb) {
    int largo = bomb->getLargoBomba();
    int x = (int) bomb->getCoordX();
    int z = (int) bomb->getCoordZ();
    bool alcanzaX = false;
    bool alcanzaZ = false;
    list<bomba*> explotadas;
    for (auto it = this->bombas.begin(); it != this->bombas.end(); it++) {
        int coordX = (int) (*it)->getCoordX();
        int coordZ = (int) (*it)->getCoordZ();
        if (x <= coordX && x + largo >= coordX) {
            alcanzaX = true;
        }
        else if (x >= coordX && x - largo <= coordX) {
            alcanzaX = true;
        }
        if (z <= coordZ && z + largo >= coordZ) {
            alcanzaZ = true;
        }
        else if (z >= coordZ && z - largo <= coordZ) {
            alcanzaZ = true;
        }
        if (alcanzaX && alcanzaZ) {
            this->bombas.erase(it);
            //aca hay que llamar al grafico para que haga efectos de exploci�n
            explotadas.push_back((*it));
        }
    }
    for (auto it = explotadas.begin(); it != explotadas.end(); it++) {
        this->explotarBomba(*it);
    }
}

void Controlador::actualizarTiempoBomba(Uint32 ms) {
    list<bomba*> explotadas;
    for (auto it = this->bombas.begin(); it != this->bombas.end(); it++) {
        (*it)->setTiempoBomba((*it)->getTiempoBomba() - ms);
        if ((*it)->getTiempoBomba() <= 0) {
            explotadas.push_back((*it));
            if ((*it)->getJugador() != nullptr) {
                (*it)->getJugador()->getBomba().erase(it);
            }
            this->bombas.erase(it);
        }
    }
    for (auto it = explotadas.begin(); it != explotadas.end(); it++) {
        this->explotarBomba((*it));
    }
}
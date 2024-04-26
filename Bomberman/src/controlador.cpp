#include "../lib/controlador.h"

Controlador* Controlador::instancia = nullptr; 

Controlador::Controlador() {
    
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
    SDL_WarpMouseInWindow(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2); //Coloca el mouse en el centro de la pantalla

    ControladorTexturas::cargarTexturas();
    ControladorObjetos::cargarObjetos();
    ControladorCamara::cambiarTipoCamara(CAMARA_ISOMETRICA);
    ControladorInterfaz::cargarInterfaz();
    ControladorAudio::cargarAudios();
}

Controlador* Controlador::getInstance() {
	if (instancia == nullptr) 
		instancia = new Controlador();

	return instancia;
}

int posBombaXTablero, posBombaZTablero;
//si ocurre el fin del juego, no se debería de poder mover ni poner bomba, pero está costando implementar eso, no es tan facil como parece
void Controlador::manejarEventos() {
    if (!finJuego) {
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
                case SDLK_t:
                    ControladorCamara::cambiarTipoCamara(CAMARA_TERCERA_PERSONA);
                    break;
                case SDLK_o:
                    ControladorCamara::cambiarTipoCamara(CAMARA_ORIGINAL);
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
                case SDLK_u:
                    ControladorAudio::playAudio(sonido::pasos);
                    break;
                case SDLK_j:
                    ControladorAudio::playAudio(sonido::bonificacion);
                    break;
                case SDLK_k:
                    ControladorAudio::playAudio(sonido::explosion);
                    break;
                case SDLK_l :
                    ControladorAudio::playAudio(sonido::muerte);
                    break;
                case SDLK_m://mute
                    ControladorAudio::detenerAudio();
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
                case SDLK_F1:
                    wireframe = !wireframe;
                    if (wireframe)
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    else
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    break;
                case SDLK_F2:
                    toggle_texturas();
                    break;
                case SDLK_F3:
                    toggle_tipoLuz();
                    if (tipoLuz)
                        glShadeModel(GL_SMOOTH);
                    else
                        glShadeModel(GL_FLAT);
                    break;
                case SDLK_F4:
                    //cambiar el color de luz (ambiente)
                    ControladorLuz::cambiarColorLuzAmbiente();
                    //Recordar hacer sombras
                    //No esta cambiando nada
                    break;
                case SDLK_F5:
                    //cambiar el color de luz (bonificador)
                    //ControladorLuz::cambiarColorLuzBonificador();
                    //Recordar hacer sombras
                    //No esta cambiando nada
                    break;
                case SDLK_F6:
                    //acelerar o disminuir velocidad de juego (global)
                    break;
                case SDLK_F7:
                    toggle_inmortal();
                    break;
                case SDLK_F11:
                    toggle_pantallaCompleta(window);
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                mouseX = (mouseX + (-evento.motion.x % 360) + 280) % 360; //No hardcodear el 280 (kevin machado)
                if (mouseX < 0)
                    mouseX += 360;

                mouseY = (mouseY + (evento.motion.y % 360)) % 360;
                if (mouseY < 0)
                    mouseY = 0;
                else if (mouseY > 360)
                    mouseY = 360;

                SDL_WarpMouseInWindow(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (evento.button.button) {
                case SDL_BUTTON_LEFT:
                    if (mouseX >= 45 && mouseX < 135) {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x - tile_size, 1);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z, 1);
                    }
                    else if (mouseX >= 135 && mouseX < 225) {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x, 1);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z + tile_size, 1);
                    }
                    else if (mouseX >= 225 && mouseX < 315) {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x + tile_size, 1);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z, 1);
                    }
                    else {
                        posBombaXTablero = getPosicionXEnTablero(jugador->getPosicion().x, 1);
                        posBombaZTablero = getPosicionXEnTablero(jugador->getPosicion().z - tile_size, 1);
                    }

                    if (bombas[posBombaXTablero][posBombaZTablero] == nullptr && estructuras[posBombaXTablero][posBombaZTablero] == nullptr && jugador->getCantBomba() < jugador->getMaxBomba()) {
                        objeto* bomba_obj = new bomba(
                            { posBombaXTablero * tile_size + tile_size / 2, 0, posBombaZTablero * tile_size + tile_size / 2 },
                            { tile_size / 4, tile_size / 2, tile_size / 4 },
                            2000, //2 segundos
                            2,
                            jugador
                        );
                        jugador->aumentarCantBomba();
                        bombas[posBombaXTablero][posBombaZTablero] = bomba_obj;

                        ControladorAudio::playAudio(sonido::explosion);
                    }
                    break;
                }
                break;
            }
        }
        //aca va Check lighting motion

    } else {
        moverArriba = false; moverAbajo = false; moverDerecha = false; moverIzquierda = false;
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_ESCAPE ) {
                fin = true;
            }
        }
    }
}

void Controlador::toggle_pantallaCompleta(SDL_Window* window) {
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    pantallaCompleta = SDL_GetWindowFlags(window) & FullscreenFlag;
    SDL_SetWindowFullscreen(window, pantallaCompleta ? 0 : FullscreenFlag);
}

void Controlador::actualizar() {
    jugador->actualizar();

    /*
        Que ocurre si la bomba_1 (i,j) revienta y alcanza a la bomba_2 (i',j') donde i'>i o j'>j?
        bomba_1 setea el tiempo de bomba_2 a 0, pero no lo actualiza al instante, tiene que esperar al proximo frame
        para que se actualice bomba_2, siendo que debería de actualizarse en el mismo frame. Alfinal solo es un frame de diferencia

        Para arreglar esto en caso de querer hacerlo, se debe modificar la función actualizar en bomba.cpp,
        basta con crear una lista de bombas explotadas, y llamar actualizar para cada una.
    */
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

    for (list<objeto*>::iterator it = particulas.begin(); it != particulas.end(); ++it)
        (*it)->actualizar();

    for (list<objeto*>::iterator it = particulas.begin(); it != particulas.end();){
        if ((*it)->getPosicion().y < 0) {
            delete (*it);
            it = particulas.erase(it);
        }
        else 
            ++it;
    }
    
    ControladorInterfaz::actualizarInterfaz();
}

void Controlador::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    ControladorCamara::colocarCamara();

    ControladorLuz::colocarLuces();

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

    for (auto it = particulas.begin(); it != particulas.end(); ++it)
        (*it)->dibujar();

    //Suelo
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glColor3f(GLfloat(227.0 / 255.0), GLfloat(186.0 / 255.0), GLfloat(143.0 / 255.0));
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, anchoTablero * tile_size);
    glVertex3f(largoTablero * tile_size, 0, anchoTablero * tile_size);
    glVertex3f(largoTablero * tile_size, 0, 0);
    glEnd();
    
    glDisable(GL_LIGHTING);

    //HUD
    ControladorInterfaz::dibujarHUD();

    SDL_GL_SwapWindow(window);
}

Controlador::~Controlador() {
    //falta hacer delete de los arreglos y punteros
    ControladorAudio::limpiarAudios();
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
};
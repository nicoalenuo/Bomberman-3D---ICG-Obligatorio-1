#include "../lib/controlador.h"

Controlador* Controlador::instancia = nullptr;

void eliminarEstructuras(vector_3 pos, bool isOrientacionX, int num) {
    int x = getIndiceTablero(pos.x);
    int z = getIndiceTablero(pos.z);

    int i = -num;
    int f = num;

    if (isOrientacionX) {
        for (i; i <= f; i++) {
            if ( x+i >= 0 && x+i < largoTablero && estructuras[x+i][z] != nullptr) {
                delete estructuras[x+i][z];
                estructuras[x+i][z] = nullptr;
            }
        }
    } else {
        for (i; i <= f; i++) {
            if (z + i >= 0 &&  z+i < anchoTablero && estructuras[x][z + i] != nullptr) {
                delete estructuras[x][z + i];
                estructuras[x][z + i] = nullptr;
            }
        }
    }
}

void Controlador::inicializar_juego() {
    if (jugador == nullptr) {
        jugador = new bomberman(
            { tile_size / 2, 0, tile_size / 2 },
            { tile_size / 6, tile_size / 2, tile_size / 6 },
            0.1f
        );
    }
    else {
        jugador->setPosicionX(tile_size / 2);
        jugador->setPosicionY(0);
        jugador->setPosicionZ(tile_size / 2);
    }

    for (int i = 0; i < largoTablero; i++) {
        for (int j = 0; j < anchoTablero; j++) {
            estructuras[i][j] = nullptr;
            bombas[i][j] = nullptr;
            fuegos[i][j] = nullptr;
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
            }
            else {
                random_num = dis(gen);
                if (random_num <= generadorTerreno) {
                    estructuras[i][j] = new estructura(
                        { (GLfloat)i * tile_size + tile_size / 2, 0, (GLfloat)j * tile_size + tile_size / 2 },
                        { tile_size / 2, tile_size, tile_size / 2 },
                        true
                    ); //destructible

                    random_num = dis(gen);
                    if (random_num <= generadorBonificador) {
                        cout << "bonificador en: " << i << " " << j << endl;
                        bonificadores[i][j] = new bonificador(
                            { (GLfloat)i * tile_size + tile_size / 2, tile_size / 2, (GLfloat)j * tile_size + tile_size / 2 },
                            { 0.1f, 0.7f, 0.1f },
                            BONIFICADOR_RANDOM
                        );
                    }

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
            { tile_size / 2, tile_size, tile_size / 2 },
            true);
    }
    if (estructuras[0][2] == nullptr) {
        estructuras[0][2] = new estructura(
            { tile_size / 2, 0, 2 * tile_size + tile_size / 2 },
            { tile_size / 2, tile_size, tile_size / 2 },
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


    for (int i = -1; i <= largoTablero; i++) { // x toma valor -1 y largoTablero en los bordes
        for (int j = -1; j <= anchoTablero; j++) { // z toma valor -1 y anchoTablero en los bordes
            for (int k = -1; k < 1; k++) { // para y toma valor -1 y 0
                if (i == -1 || i == largoTablero || j == -1 || j == anchoTablero) {
                    objeto* est = new estructura(
                        { (GLfloat)i * tile_size + tile_size / 2,(GLfloat)k * tile_size, (GLfloat)j * tile_size + tile_size / 2 },
                        { tile_size / 2, tile_size, tile_size / 2 },
                        false
                    );
                    borde.push_back(est);
                }
            }
        }
    }

    int cantidad_enemigos_colocados = 0;
    vector<pair<int, int>> posEnemigos;

    while (cantidad_enemigos_colocados < cantidad_enemigos_actual) {
        int posicion_enemigo_x = dis(gen)*(largoTablero - 1);
        int posicion_enemigo_z = dis(gen)*(anchoTablero - 1);
        if (int(posicion_enemigo_x) % 2 == 0 &&
            int(posicion_enemigo_z) % 2 == 0 &&
            estructuras[getIndiceTablero(int(posicion_enemigo_x))][getIndiceTablero(int(posicion_enemigo_z))] == nullptr &&
            int(posicion_enemigo_x) + int(posicion_enemigo_z) > 6) {
            posEnemigos.push_back({ int(posicion_enemigo_x), int(posicion_enemigo_z)});
            cantidad_enemigos_colocados++;
        }
    }

    enemigo* enem;
    bool orientacionX;
    double prob;

    for (vector<pair<int, int>>::iterator itP = posEnemigos.begin(); itP != posEnemigos.end(); itP++) { 
        prob = dis(gen);
        orientacionX = (prob < 0.5);
        enem = new enemigo(
            { (GLfloat)(itP->first) * tile_size + tile_size / 2, 0, (GLfloat)(itP->second) * tile_size + tile_size / 2 },
            { GLfloat(tile_size / 4), tile_size, GLfloat(tile_size / 4) },
            orientacionX,
            (prob < 0.33?ROJO: (prob < 0.66? AZUL:VERDE))
        );

        eliminarEstructuras(enem->getPosicion(), enem->getOrientacionX(), 3);

        enemigos.push_back(enem);
    }

    bool puertaColocada = false;
    while (!puertaColocada) {
        int posicion_puerta_x = dis(gen) * (largoTablero - 1);
        int posicion_puerta_z = dis(gen) * (anchoTablero - 1);
        if (estructuras[posicion_puerta_x][posicion_puerta_z] != nullptr && 
            dynamic_cast<estructura*>(estructuras[posicion_puerta_x][posicion_puerta_z])->getDestructible() &&
            posicion_puerta_x + posicion_puerta_z > 6) {
            puertaColocada = true;
            puerta = new door(
                { GLfloat(posicion_puerta_x * tile_size + tile_size / 2), 0, GLfloat(posicion_puerta_z * tile_size + tile_size / 2) },
                { GLfloat(tile_size / 2), tile_size / 4, GLfloat(tile_size / 2) }
            );
            cout << posicion_puerta_x << endl;
            cout << posicion_puerta_z << endl;
        }
    }

    current_t = chrono::high_resolution_clock::now();
    puertaAbierta = false;
}

Controlador::Controlador() {
    for (int i = 0; i < largoTablero; i++) {
        estructuras[i] = new objeto * [anchoTablero];
        bombas[i] = new objeto * [anchoTablero];
        fuegos[i] = new objeto * [anchoTablero];
        bonificadores[i] = new objeto * [anchoTablero];
    }

    cantidad_enemigos_actual = 4;

    inicializar_juego();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    window = SDL_CreateWindow(
        "Bomberman 3D",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    context = SDL_GL_CreateContext(window);

    if (context == NULL) {
        cerr << "[GL Context Error]: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

	if (TTF_Init() < 0) {
		cerr << "[SDL TTF Error]: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}

    glMatrixMode(GL_PROJECTION);

    glClearColor(0.52f, 0.80f, 0.92f, 1.0f); //Celeste

    gluPerspective(45, WINDOW_RATIO, 1, 200);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);

    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    controlador_texturas = ControladorTexturas::getInstance();
    controlador_objetos = ControladorObjetos::getInstance();
    controlador_audio = ControladorAudio::getInstance();
    controlador_luz = ControladorLuz::getInstance();
    controlador_poderes = ControladorPoderes::getInstance();
    controlador_camara = ControladorCamara::getInstance();
    controlador_interfaz = ControladorInterfaz::getInstance();

    controlador_audio->playAudio(sonido::inicioJuego);
}

Controlador* Controlador::getInstance() {
	if (instancia == nullptr) 
		instancia = new Controlador();

	return instancia;
}

int posBombaXTablero, posBombaZTablero;
inline void colocarBomba(ControladorCamara* controlador_camara, ControladorPoderes* controlador_poderes, ControladorAudio* controlador_audio) {
    if (jugador->bombaDisponible()) {
        if (controlador_camara->camaraMiraHacia(EJE_MENOS_X)) {
            posBombaXTablero = getIndiceTablero(jugador->getPosicion().x - tile_size);
            posBombaZTablero = getIndiceTablero(jugador->getPosicion().z);
        }
        else if (controlador_camara->camaraMiraHacia(EJE_Z)) {
            posBombaXTablero = getIndiceTablero(jugador->getPosicion().x);
            posBombaZTablero = getIndiceTablero(jugador->getPosicion().z + tile_size);
        }
        else if (controlador_camara->camaraMiraHacia(EJE_X)) {
            posBombaXTablero = getIndiceTablero(jugador->getPosicion().x + tile_size);
            posBombaZTablero = getIndiceTablero(jugador->getPosicion().z);
        }
        else {
            posBombaXTablero = getIndiceTablero(jugador->getPosicion().x);
            posBombaZTablero = getIndiceTablero(jugador->getPosicion().z - tile_size);
        }

        if (posBombaXTablero >= 0 && posBombaXTablero < largoTablero &&
            posBombaZTablero >= 0 && posBombaZTablero < anchoTablero &&
            bombas[posBombaXTablero][posBombaZTablero] == nullptr &&
            estructuras[posBombaXTablero][posBombaZTablero] == nullptr) 
        {
            jugador->aumentarCantBomba();

            objeto* bomba_obj = new bomba(
                { posBombaXTablero * tile_size + tile_size / 2, 1, posBombaZTablero * tile_size + tile_size / 2 },
                { tile_size / 4, tile_size / 2, tile_size / 4 },
                2000, //2 segundos
                1 + controlador_poderes->getValor(AUMENTAR_ALCANCE_BOMBAS),
                controlador_audio->playMecha({ posBombaXTablero * tile_size + tile_size / 2, 0, posBombaZTablero * tile_size + tile_size / 2 })
            );
            bombas[posBombaXTablero][posBombaZTablero] = bomba_obj;

            if (bonificadores[posBombaXTablero][posBombaZTablero] != nullptr) {
                delete bonificadores[posBombaXTablero][posBombaZTablero];
                bonificadores[posBombaXTablero][posBombaZTablero] = nullptr;
            }
        }
    }
}

void Controlador::manejarEventos() {
    if (pausa) {
        while (SDL_PollEvent(&evento)) {
            switch (evento.type) {
            case SDL_KEYDOWN:
                switch (evento.key.keysym.sym) {
                case SDLK_p:
                    pausa = false;
                    break;
                case SDLK_ESCAPE:
                    fin = true;
                case SDLK_UP:
                    controlador_interfaz->opcion_anterior();
                    break;
                case SDLK_DOWN:
                    controlador_interfaz->opcion_siguiente();
                    break;
                case SDLK_RETURN:
                    controlador_interfaz->seleccionar_opcion();
                    break;
                }
                break;
            }
        }
        return;
    }

    if (finJuego) {
        moverArriba = false; moverAbajo = false; moverDerecha = false; moverIzquierda = false;
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_KEYDOWN) {
                if (evento.key.keysym.sym == SDLK_ESCAPE)
                    fin = true;
                else if (evento.key.keysym.sym == SDLK_p)
                    toggle(pausa);
            }
        }
        return;
    }

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
                    colocarBomba(controlador_camara, controlador_poderes, controlador_audio);
                    break;
                case SDLK_p:
                    toggle(pausa);
                    if (pausa) {
                        controlador_audio->pausarAudio();
                    } else {
                        controlador_audio->reanudarAudio();
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
                case SDLK_1:
                    controlador_audio->playAudio(sonido::muerte);
                    break;
                case SDLK_2:
                    controlador_audio->playAudio(sonido::bonificacion);
                    break;
                case SDLK_3:
                    controlador_audio->playBomba({0,0,0});
                    break;
                case SDLK_4 :
                    controlador_audio->playAudio(sonido::pasos);
                case SDLK_5:
                    controlador_audio->playAudio(sonido::inicioJuego);
                case SDLK_6:
                    controlador_audio->playAudio(sonido::puertaAbierta);
                    break;
                case SDLK_7:
                    controlador_audio->playAudio(sonido::musica);
                    break;
                case SDLK_8:
                    controlador_audio->playMecha({ 0,0,0 });
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
                case SDLK_F11:
                    SDL_SetWindowFullscreen(window, SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN ? 0 : SDL_WINDOW_FULLSCREEN);
                    break;
            }
        break;
        case SDL_MOUSEMOTION:
            mouseX = GLfloat(fmod(mouseX - (evento.motion.xrel * SENSIBILIDAD_MOUSE), 360));
            if (mouseX < 0)
                mouseX += 360;

            mouseY = mouseY - (evento.motion.yrel * SENSIBILIDAD_MOUSE);
            if (mouseY < 1)
                mouseY = 1;
            else if (mouseY > 90)
                mouseY = 90;

            mouseY_invertido = mouseY_invertido + (evento.motion.yrel * SENSIBILIDAD_MOUSE);
            if (mouseY_invertido < 5)
                mouseY_invertido = 5;
            else if (mouseY_invertido > 90)
                mouseY_invertido = 90;
        break;
        case SDL_MOUSEBUTTONDOWN:
            switch (evento.button.button) {
                case SDL_BUTTON_LEFT:
                    colocarBomba(controlador_camara, controlador_poderes, controlador_audio);
                break;
            }
        break;
        }
    }
    const Uint8* movimientoCamara = SDL_GetKeyboardState(NULL);

    if (movimientoCamara[SDL_SCANCODE_I]) {
        controlador_luz->moverCamara({ 0, 0, -(float)(velocidadCamara * velocidad_juego * frameDelay / 1000) });
    }
    if (movimientoCamara[SDL_SCANCODE_J]) {
        controlador_luz->moverCamara({ -(float)(velocidadCamara * velocidad_juego * frameDelay / 1000), 0, 0 });
    }
    if (movimientoCamara[SDL_SCANCODE_K]) {
        controlador_luz->moverCamara({ 0, 0, (float)(velocidadCamara * velocidad_juego * frameDelay / 1000) });
    }
    if (movimientoCamara[SDL_SCANCODE_L]) {
        controlador_luz->moverCamara({ (float)(velocidadCamara * velocidad_juego * frameDelay / 1000), 0, 0 });
    }
}

void Controlador::actualizar() {
    previous_t = current_t;
    current_t = chrono::high_resolution_clock::now();
    delta_time = chrono::duration_cast<chrono::duration<int>>((current_t - previous_t)*1000);
    elapsed_time = delta_time.count() * velocidad_juego + 1;

    if (pausa) {
        mouseX += 0.3f * (elapsed_time / frameDelay) * velocidad_juego;
        return;
    }

    if (!pausa && !finJuego && !pararTiempo)
        disminuirTiempo(elapsed_time);

    if (puertaAbierta && puerta->intersecta(jugador)) {
        controlador_audio->playAudio(sonido::bonificacion);
        controlador_poderes->resetearPoderes();
        cantidad_enemigos_actual++;
        aumentarNivel();
        inicializar_juego();
    } 

    controlador_poderes->actualizarTemporizadores();

    jugador->actualizar();
    puerta->actualizar();

    for (int i = 0; i < largoTablero; i++) {
        for (int j = 0; j < anchoTablero; j++) {
            if (bombas[i][j] != nullptr) {
                bombas[i][j]->actualizar();
            }

            if (fuegos[i][j] != nullptr) {
                fuegos[i][j]->actualizar();
            }

            if (bonificadores[i][j] != nullptr){
                bonificadores[i][j]->actualizar();
            }
        }
    }

    for (list<particula*>::iterator it = particulas.begin(); it != particulas.end(); /*se actualiza dentro del bucle */) {
        (*it)->actualizar();
        if ((*it)->getEliminar()) {
            delete (*it);
            it = particulas.erase(it);
        }
        else {
            ++it;
        }
    }

    for (list<enemigo*>::iterator itE = enemigos.begin(); itE != enemigos.end();){
        if (!inmortal && !controlador_poderes->getValor(INMORTALIDAD) && (*itE)->intersecta(jugador)) {
            finJuego = true;
        }
        (*itE)->actualizar();
        if ((*itE)->getEliminar()) {
            delete (*itE);
            itE = enemigos.erase(itE);
        }
        else {
            itE++;
        }
    }

    if (!puertaAbierta && enemigos.empty()) {
        puertaAbierta = true;
        controlador_audio->playAudio(sonido::puertaAbierta, puerta->getPosicion());
    }

    if (!temporizador && tiempoJuego <= 10000) {
        temporizador = true;
        controlador_audio->playAudio(sonido::timer10);
    }
}

void Controlador::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    controlador_camara->colocarCamara(jugador->getPosicion());

    if (texturas_habilitadas) {
        controlador_luz->colocarLuces(jugador->getPosicion());
    }

    controlador_objetos->dibujarSuelo();
    jugador->dibujar();

    for (int i = 0; i < largoTablero; i++) {
        for (int j = 0; j < anchoTablero; j++) {
            if (estructuras[i][j] != nullptr) {
                estructuras[i][j]->dibujar();
            }

            if (bombas[i][j] != nullptr) {
                bombas[i][j]->dibujar();
            }
        }
    }

    for (list<objeto*>::iterator itBorde = borde.begin(); itBorde != borde.end(); ++itBorde){
        (*itBorde)->dibujar();
    }

    for (list<enemigo*>::iterator itE = enemigos.begin(); itE != enemigos.end(); itE++){
        (*itE)->dibujar();
    }

    puerta->dibujar();

    controlador_luz->quitarLuces();

    for (int i = 0; i < largoTablero; i++) {
        for (int j = 0; j < anchoTablero; j++) {
            if (bonificadores[i][j] != nullptr) {
                bonificadores[i][j]->dibujar();
            }
        }
    }

    for (list<particula*>::iterator it = particulas.begin(); it != particulas.end(); ++it) {
        (*it)->dibujar();
    }

    controlador_objetos->dibujarMarcadorBomba(jugador->getPosicion());

    if (pausa) {
        controlador_interfaz->dibujarMenu();
    }

    if (mostrarHud) {
        controlador_interfaz->dibujarHUD();
    }

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

            if (bonificadores[i][j] != nullptr)
                delete bonificadores[i][j];
        }
    }

    for (list<particula*>::iterator it = particulas.begin(); it != particulas.end();) {
        delete (*it);
        it = particulas.erase(it);
    }

    for (list<objeto*>::iterator itBorde = borde.begin(); itBorde != borde.end();){
        delete (*itBorde);
        itBorde = borde.erase(itBorde);
    }

    for (list<enemigo*>::iterator itE = enemigos.begin(); itE != enemigos.end();) {
        (*itE)->dibujar();
        itE = enemigos.erase(itE);
    }


    delete controlador_texturas;
    delete controlador_objetos;
    delete controlador_audio;
    delete controlador_luz;
    delete controlador_poderes;
    delete controlador_camara;
    delete controlador_interfaz;

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
};
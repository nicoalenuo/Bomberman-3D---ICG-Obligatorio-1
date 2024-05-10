#include "../lib/ControladorInterfaz.h"

ControladorInterfaz* ControladorInterfaz::instancia = nullptr;

float const MARGEN_HUD = 5.0f;
float MARGEN_PODERES = 30.f * WINDOW_RATIO;
float posXPoder = MARGEN_HUD;
vector_3 margen_left = { MARGEN_HUD,MARGEN_HUD,0 };

ControladorInterfaz* ControladorInterfaz::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorInterfaz();
	return instancia;
}

ControladorInterfaz::ControladorInterfaz() {
	tipoOpcion = true;
	opcion_seleccionada = COMENZAR_JUEGO;

	interfaz = TTF_OpenFont("texturas/OpenSans-Regular.ttf", 24);
	if (interfaz == nullptr) {
		cerr << "Error en TTF_OpenFont: " << SDL_GetError() << endl;
		return;
	}

	hudTiempo = new hud();
	hudEnemigos = new hud();
	hudPuntaje = new hud();
	hudNivel = new hud();
	hudGameOver = new hud();

	for (int i = 0; i < int(tipo_poder::BONIFICADOR_RANDOM); i++) {
		poderes[static_cast<tipo_poder>(i)] = new hud();
		poderes[static_cast<tipo_poder>(i)]->colorMensaje = { 255, 255, 255 };
		poderes[static_cast<tipo_poder>(i)]->posicion = position::bottom_left;
	}

	hudTiempo->colorMensaje = { 255, 255, 255 };
	hudEnemigos->colorMensaje = { 255,255,255 };
	hudPuntaje->colorMensaje = { 255, 255, 255 };
	hudNivel->colorMensaje = { 255 ,255 ,255 };
	hudGameOver->colorMensaje = { 255, 255, 255 };

	hudTiempo->posicion = position::top_left;
	hudEnemigos->posicion = position::left;
	hudPuntaje->posicion = position::top_right;
	hudNivel->posicion = position::top_center;
	hudGameOver->posicion = position::center;

	//Menu

	for (int i = int(COMENZAR_JUEGO); i <= int(CERRAR_JUEGO); i++) {
		opciones_inicio[tipo_opcion(i)] = new hud();
		opciones_inicio[tipo_opcion(i)]->colorMensaje = { 255, 255, 255 };
	}


	for (int i = int(CAMBIAR_CAMARA); i <= int(ATRAS); i++) {
		opciones_configuracion[tipo_opcion(i)] = new hud();
		opciones_configuracion[tipo_opcion(i)]->colorMensaje = { 255, 255, 255 };
	}

	opciones_actuales = opciones_inicio;
	//Fin menu
}


void ControladorInterfaz::setPoderes(map<tipo_poder, int> powerUp){
	for (auto it = powerUp.begin(); it != powerUp.end(); ++it) {
		if (ControladorPoderes::getInstance()->poderDependeDeTiempo(it->first)) {
			setMensajeEnComponente(to_string(it->second / 1000) + "s", interfaz, poderes[it->first]);
		} else {
			string mensaje = to_string(it->second);
			if (it->first == AUMENTAR_CANTIDAD_BOMBAS) {
				mensaje = to_string((it->second + 1) - jugador->getCantBomba());
			}
			setMensajeEnComponente(mensaje + "x", interfaz, poderes[it->first]);
		}
	}
}

void ControladorInterfaz::setMensajeEnComponente(string mensaje, TTF_Font* fuente, hud* componente) {
	glColor3f(componente->colorMensaje.r, componente->colorMensaje.g, componente->colorMensaje.b);
	if (componente->mensajeSurface != NULL) {
		SDL_FreeSurface(componente->mensajeSurface);
	}
	componente->mensajeSurface = TTF_RenderText_Blended(fuente, mensaje.c_str(), { 255, 255, 255 });
	if (componente->mensajeSurface == NULL) { 
		cerr << "TTF_RenderText error: " << SDL_GetError() << endl;
		return;
	}

	glDeleteTextures(1, &(componente->idTextura));
	glGenTextures(1, &(componente->idTextura));

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, componente->idTextura);

	TTF_SizeText(fuente, mensaje.c_str(), &(componente->width), &(componente->height));

	if (componente->colorSurface != NULL) {
		SDL_FreeSurface(componente->colorSurface);
	}
	componente->colorSurface = SDL_CreateRGBSurface(0, componente->width, componente->height, 32,
		0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	if (componente->colorSurface == NULL) {
		cerr << "SDL_CreateRGBSurface() failed: " << SDL_GetError() << endl;
		exit(1);
	}

	if (componente->colorSurface != nullptr) {
		SDL_FillRect(componente->colorSurface, nullptr, SDL_MapRGBA(componente->colorSurface->format, 255, 255, 255, 0)); // Componente alfa en 0 para transparencia
	}

	SDL_BlitSurface(componente->mensajeSurface, NULL, componente->colorSurface, NULL);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, componente->width, componente->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, componente->colorSurface->pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void ControladorInterfaz::dibujarComponenteHUDPoderes() {
	posXPoder = MARGEN_HUD;
	for (pair<const tipo_poder, hud*>& kv : poderes) {
		if (kv.first==AUMENTAR_CANTIDAD_BOMBAS || ControladorPoderes::getInstance()->getValor(kv.first) != 0) {
			//dibujar texto
			if (!ControladorPoderes::getInstance()->poderEsBooleano(kv.first)) {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, kv.second->idTextura);
				glColor3f(kv.second->colorMensaje.r, kv.second->colorMensaje.g, kv.second->colorMensaje.b);

				glBegin(GL_QUADS); {
					glTexCoord2d(0.f, 1.f); glVertex3f(posXPoder, altoPantalla - MARGEN_HUD, 0.f);
					glTexCoord2d(1.f, 1.f); glVertex3f(posXPoder + kv.second->width, altoPantalla - MARGEN_HUD, 0.f);
					glTexCoord2d(1.f, 0.f); glVertex3f(posXPoder + kv.second->width, altoPantalla - MARGEN_HUD - kv.second->height, 0.f);
					glTexCoord2d(0.f, 0.f); glVertex3f(posXPoder, altoPantalla - MARGEN_HUD - kv.second->height, 0.f);
				} glEnd();

				glDisable(GL_TEXTURE_2D);

				posXPoder += kv.second->width;
			}

			//dibujar icono
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, ControladorTexturas::getInstance()->getTextura(ControladorTexturas::getInstance()->getTipoTexturaPoder(kv.first)));
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 1.f); glVertex3f(posXPoder, altoPantalla - MARGEN_HUD - kv.second->height, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(posXPoder + kv.second->height, altoPantalla - MARGEN_HUD - kv.second->height, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(posXPoder + kv.second->height, altoPantalla - MARGEN_HUD, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(posXPoder, altoPantalla - MARGEN_HUD, 0.f);
			}glEnd();
			glDisable(GL_TEXTURE_2D);

			posXPoder += kv.second->height + MARGEN_PODERES;
		}
	}
}

void ControladorInterfaz::dibujarComponenteHUD(hud* hud) {
	switch (hud->posicion) {
		case position::top_left:
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, hud->idTextura);
			glColor3f(hud->colorMensaje.r, hud->colorMensaje.g, hud->colorMensaje.b);
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 1.f); glVertex3f(margen_left.x, margen_left.y + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(margen_left.x + hud->mensajeSurface->w, margen_left.y + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(margen_left.x + hud->mensajeSurface->w, margen_left.y, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(margen_left.x, margen_left.y, 0.f);
			} glEnd();
			glDisable(GL_TEXTURE_2D);
			margen_left.y = MARGEN_HUD*3 + hud->mensajeSurface->h;
			break;
		case position::top_right:
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, hud->idTextura);
			glColor3f(hud->colorMensaje.r, hud->colorMensaje.g, hud->colorMensaje.b);
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 1.f); glVertex3f(largoPantalla - MARGEN_HUD - hud->mensajeSurface->w, MARGEN_HUD + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(largoPantalla - MARGEN_HUD, MARGEN_HUD + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(largoPantalla - MARGEN_HUD, MARGEN_HUD, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(largoPantalla - MARGEN_HUD - hud->mensajeSurface->w, MARGEN_HUD, 0.f);
			} glEnd();
			glDisable(GL_TEXTURE_2D);
			break;
		case position::top_center:
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, hud->idTextura);
			glColor3f(hud->colorMensaje.r, hud->colorMensaje.g, hud->colorMensaje.b);
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 1.f); glVertex3f(largoPantalla / 2.f - hud->mensajeSurface->w / 2.f, MARGEN_HUD + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(largoPantalla / 2.f + hud->mensajeSurface->w / 2.f, MARGEN_HUD + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(largoPantalla / 2.f + hud->mensajeSurface->w / 2.f, MARGEN_HUD, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(largoPantalla / 2.f - hud->mensajeSurface->w / 2.f, MARGEN_HUD, 0.f);
			} glEnd();
			glDisable(GL_TEXTURE_2D);
			break;
		case position::left: 
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, hud->idTextura);
			glColor3f(hud->colorMensaje.r, hud->colorMensaje.g, hud->colorMensaje.b);
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 1.f); glVertex3f(margen_left.x, margen_left.y + MARGEN_HUD + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(margen_left.x + hud->mensajeSurface->w, margen_left.y + MARGEN_HUD + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(margen_left.x + hud->mensajeSurface->w, margen_left.y + MARGEN_HUD, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(margen_left.x, margen_left.y + MARGEN_HUD, 0.f);
			} glEnd();
			glDisable(GL_TEXTURE_2D);

			margen_left.x += hud->mensajeSurface->w + MARGEN_HUD;
			margen_left.y += MARGEN_HUD;
			//falta dibujar una imagen de amongos a la derecha del numero
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, ControladorTexturas::getInstance()->getTextura(TEXTURA_CANT_ENEMIGOS));
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 0.f); glVertex3f(margen_left.x, margen_left.y + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(margen_left.x + hud->mensajeSurface->h, margen_left.y + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(margen_left.x + hud->mensajeSurface->h, margen_left.y, 0.f);
				glTexCoord2d(0.f, 1.f); glVertex3f(margen_left.x, margen_left.y, 0.f);
			} glEnd();
			glDisable(GL_TEXTURE_2D);
			break;
		case position::center: //cambiar los valores de vertex
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, hud->idTextura);
			glColor3f(hud->colorMensaje.r, hud->colorMensaje.g, hud->colorMensaje.b);
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 1.f); glVertex3f(largoPantalla / 2.f - hud->mensajeSurface->w / 2.f, altoPantalla / 2.f + hud->mensajeSurface->h / 2.f, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(largoPantalla / 2.f + hud->mensajeSurface->w / 2.f, altoPantalla / 2.f + hud->mensajeSurface->h / 2.f, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(largoPantalla / 2.f + hud->mensajeSurface->w / 2.f, altoPantalla / 2.f - hud->mensajeSurface->h / 2.f, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(largoPantalla / 2.f - hud->mensajeSurface->w / 2.f, altoPantalla / 2.f - hud->mensajeSurface->h / 2.f, 0.f);
			} glEnd();
			glDisable(GL_TEXTURE_2D);
			break;
	}
}

void ControladorInterfaz::dibujarMenu() {
	GLfloat posY = (altoPantalla / 2.0f) - 150;

	setMensajeEnComponente(
		(opcion_seleccionada == COMENZAR_JUEGO ? string("->") : "") + "Jugar" + (opcion_seleccionada == COMENZAR_JUEGO ? string("<-") : ""),
		interfaz, opciones_inicio[COMENZAR_JUEGO]);
	setMensajeEnComponente(
		(opcion_seleccionada == CONFIGURACIONES ? string("->") : "") + "Configuraciones" + (opcion_seleccionada == CONFIGURACIONES ? string("<-") : ""),
		interfaz, opciones_inicio[CONFIGURACIONES]);
	setMensajeEnComponente(
		(opcion_seleccionada == AYUDA ? string("->") : "") + "Ayuda" + (opcion_seleccionada == AYUDA ? string("<-") : ""),
		interfaz, opciones_inicio[AYUDA]);
	setMensajeEnComponente(
		(opcion_seleccionada == CERRAR_JUEGO ? string("->") : "") + "Cerrar Juego" + (opcion_seleccionada == CERRAR_JUEGO ? string("<-") : ""),
		interfaz, opciones_inicio[CERRAR_JUEGO]);

	//Toggle camara
	setMensajeEnComponente(
		(opcion_seleccionada == CAMBIAR_CAMARA ? string("->") : "") + "Camara" + (opcion_seleccionada == CAMBIAR_CAMARA ? string("<-") : ""),
		interfaz, opciones_configuracion[CAMBIAR_CAMARA]);

	// Toggle Wireframe
	setMensajeEnComponente((opcion_seleccionada == TOGGLE_WIREFRAME ? string("->") : "") + "Wireframe : " + (wireframe ? "Line" : "Fill") + (opcion_seleccionada == TOGGLE_WIREFRAME ? string("<-") : ""),
		interfaz, opciones_configuracion[TOGGLE_WIREFRAME]);

	// Toggle Texturas
	setMensajeEnComponente((opcion_seleccionada == TOGGLE_TEXTURAS ? string("->") : "") + " Texturas : " + (texturas_habilitadas ? "Habilitadas" : "Deshabilitadas") + (opcion_seleccionada == TOGGLE_TEXTURAS ? string("<-") : ""),
		interfaz, opciones_configuracion[TOGGLE_TEXTURAS]);

	// Toggle Tipo Luz
	setMensajeEnComponente((opcion_seleccionada == TOGGLE_TIPO_LUZ ? string("->") : "") + "Tipo Luz : " + (tipoLuz ? "Smooth" : "Flat") + (opcion_seleccionada == TOGGLE_TIPO_LUZ ? string("<-") : ""),
		interfaz, opciones_configuracion[TOGGLE_TIPO_LUZ]);

	// Toggle Luz Ambiente
	setMensajeEnComponente((opcion_seleccionada == TOGGLE_LUZ_AMBIENTE ? string("->") : "") + "Luz Ambiente" + (opcion_seleccionada == TOGGLE_LUZ_AMBIENTE ? string("<-") : ""),
		interfaz, opciones_configuracion[TOGGLE_LUZ_AMBIENTE]);

	// Toggle HUD
	setMensajeEnComponente((opcion_seleccionada == TOGGLE_HUD ? string("->") : "") + "HUD : " + (mostrarHud ? "Habilitado" : "Deshabilitado") + (opcion_seleccionada == TOGGLE_HUD ? string("<-") : ""),
		interfaz, opciones_configuracion[TOGGLE_HUD]);

	// Toggle Velocidad Juego
	setMensajeEnComponente((opcion_seleccionada == TOGGLE_VELOCIDAD_JUEGO ? string("->") : "") + "Velocidad Juego : " + to_string(velocidad_juego) + (opcion_seleccionada == TOGGLE_VELOCIDAD_JUEGO ? string("<-") : ""),
		interfaz, opciones_configuracion[TOGGLE_VELOCIDAD_JUEGO]);

	// Toggle Inmortal
	setMensajeEnComponente((opcion_seleccionada == TOGGLE_INMORTAL ? string("->") : "") + "Inmortalidad : " + (inmortal ? "Habilitado" : "Deshabilitado") + (opcion_seleccionada == TOGGLE_INMORTAL ? string("<-") : ""),
		interfaz, opciones_configuracion[TOGGLE_INMORTAL]);

	// Toggle Parar Tiempo
	setMensajeEnComponente((opcion_seleccionada == TOGGLE_PARAR_TIEMPO ? string("->") : "") + "Parar Tiempo : " + (pararTiempo ? "Habilitado" : "Deshabilitado") + (opcion_seleccionada == TOGGLE_PARAR_TIEMPO ? string("<-") : ""),
		interfaz, opciones_configuracion[TOGGLE_PARAR_TIEMPO]);

	// Toggle Atravesar Paredes
	setMensajeEnComponente((opcion_seleccionada == TOGGLE_ATRAVESAR_PAREDES ? string("->") : "") + "Atravesar Paredes : " + (atravesar_paredes ? "Habilitado" : "Deshabilitado") + (opcion_seleccionada == TOGGLE_ATRAVESAR_PAREDES ? string("<-") : ""),
		interfaz, opciones_configuracion[TOGGLE_ATRAVESAR_PAREDES]);

	// Toggle Audio
	setMensajeEnComponente((opcion_seleccionada == TOGGLE_AUDIO ? string("->") : "") + "Sonidos : " + (!mute ? "Habilitados" : "Deshabilitados") + (opcion_seleccionada == TOGGLE_AUDIO ? string("<-") : ""),
		interfaz, opciones_configuracion[TOGGLE_AUDIO]);

	// Toggle Pantalla Completa
	setMensajeEnComponente((opcion_seleccionada == TOGGLE_PANTALLA ? string("->") : "") + "Pantalla : " + (!pantallaCompleta ? "Normal" : "Completa") + (opcion_seleccionada == TOGGLE_PANTALLA ? string("<-") : ""),
		interfaz, opciones_configuracion[TOGGLE_PANTALLA]);

	setMensajeEnComponente((opcion_seleccionada == ATRAS ? string("->") : "") + "Atras" + (opcion_seleccionada == ATRAS ? string("<-") : ""),
		interfaz, opciones_configuracion[ATRAS]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();

	glOrtho(0, largoPantalla, altoPantalla, 0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ControladorTexturas::getInstance()->getTextura(TEXTURA_LOGO));
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS); {
		glTexCoord2d(0.f, 1.f); glVertex3f((largoPantalla / 2.0f) - 200, (altoPantalla / 2.0f) - 300, 0.f);
		glTexCoord2d(1.f, 1.f); glVertex3f((largoPantalla / 2.0f) + 200, (altoPantalla / 2.0f) - 300, 0.f);
		glTexCoord2d(1.f, 0.f); glVertex3f((largoPantalla / 2.0f) + 200, (altoPantalla / 2.0f) - 200, 0.f);
		glTexCoord2d(0.f, 0.f); glVertex3f((largoPantalla / 2.0f) - 200, (altoPantalla / 2.0f) - 200, 0.f);
	}glEnd();
	glDisable(GL_TEXTURE_2D);

	for (pair<const tipo_opcion, hud*>& kv : opciones_actuales) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, kv.second->idTextura);
		glColor3f(kv.second->colorMensaje.r, kv.second->colorMensaje.g, kv.second->colorMensaje.b);
		glBegin(GL_QUADS); {
			glTexCoord2d(0.f, 1.f); glVertex3f((largoPantalla / 2.0f) - (kv.second->width / 2.0f), posY + kv.second->height, 0.f);
			glTexCoord2d(1.f, 1.f); glVertex3f((largoPantalla / 2.0f) + (kv.second->width / 2.0f), posY + kv.second->height, 0.f);
			glTexCoord2d(1.f, 0.f); glVertex3f((largoPantalla / 2.0f) + (kv.second->width / 2.0f), posY, 0.f);
			glTexCoord2d(0.f, 0.f); glVertex3f((largoPantalla / 2.0f) - (kv.second->width / 2.0f), posY, 0.f);
		} glEnd();
		glDisable(GL_TEXTURE_2D);

		posY += 40;
	}

	glPopMatrix();

	glMatrixMode(GL_PROJECTION); glPopMatrix();
	glMatrixMode(GL_MODELVIEW); glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void ControladorInterfaz::opcion_anterior() {
	if (tipoOpcion) { // esta entre tipo_opcion::COMENZAR_JUEGO y tipo_opcion::CERRAR_JUEGO (0 a 3)
		if (opcion_seleccionada == tipo_opcion::COMENZAR_JUEGO) {
			opcion_seleccionada = tipo_opcion::CERRAR_JUEGO;
		} else {
			opcion_seleccionada = tipo_opcion((int(opcion_seleccionada) - 1));
		}
	} else { // esta entre tipo_opcion::CAMBIAR_CAMARA y tipo_opcion::ATRAS 4 a 15
		if (opcion_seleccionada == tipo_opcion::CAMBIAR_CAMARA) {
			opcion_seleccionada = tipo_opcion::ATRAS;
		} else {
			opcion_seleccionada = tipo_opcion((int(opcion_seleccionada) - 1));
		}
	}
}

void ControladorInterfaz::opcion_siguiente() {
	if (tipoOpcion) { // esta entre tipo_opcion::COMENZAR_JUEGO y tipo_opcion::CERRAR_JUEGO (0 a 3)
		if (opcion_seleccionada == tipo_opcion::CERRAR_JUEGO) {
			opcion_seleccionada = tipo_opcion::COMENZAR_JUEGO;
		}
		else {
			opcion_seleccionada = tipo_opcion((int(opcion_seleccionada) + 1));
		}
	}
	else { // esta entre tipo_opcion::CAMBIAR_CAMARA y tipo_opcion::ATRAS 4 a 15
		if (opcion_seleccionada == tipo_opcion::ATRAS) {
			opcion_seleccionada = tipo_opcion::CAMBIAR_CAMARA;
		}
		else {
			opcion_seleccionada = tipo_opcion((int(opcion_seleccionada) + 1));
		}
	}
}

void ControladorInterfaz::dibujarHUD() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	margen_left = { MARGEN_HUD, MARGEN_HUD, 0 };

	setMensajeEnComponente("Puntaje: " + to_string(puntaje), interfaz, hudPuntaje);
	setMensajeEnComponente(to_string(enemigos.size()), interfaz, hudEnemigos);
	setMensajeEnComponente("Tiempo: " + to_string(tiempoJuego / 1000), interfaz, hudTiempo);
	if (finJuego) {
		setMensajeEnComponente("¡PERDISTE!", interfaz, hudGameOver);
	} else if(enemigos.size() == 0 && !puertaAbierta) {
		setMensajeEnComponente("Encuentra el portal escondido", interfaz, hudGameOver);
	} else if (enemigos.size() == 0) {
		setMensajeEnComponente("Ingresa a la puerta", interfaz, hudGameOver);
	} else {
		setMensajeEnComponente(" ", interfaz, hudGameOver);
	}

	setMensajeEnComponente("Nivel " + to_string(nivel), interfaz, hudNivel);

	setPoderes(ControladorPoderes::getInstance()->obtenerPoderes());

	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();

	glOrtho(0, largoPantalla, altoPantalla, 0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();

	glPushMatrix();

	dibujarComponenteHUD(hudTiempo);
	dibujarComponenteHUD(hudPuntaje);
	dibujarComponenteHUD(hudNivel);
	dibujarComponenteHUD(hudEnemigos);
	if (finJuego) {
		dibujarComponenteHUD(hudGameOver);
	}

	dibujarComponenteHUDPoderes(); 

	glPopMatrix();

	glMatrixMode(GL_PROJECTION); glPopMatrix();
	glMatrixMode(GL_MODELVIEW); glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}



bool ControladorInterfaz::getTipoOpcion() {
	return this->tipoOpcion;
}

void ControladorInterfaz::setTipoOpcion(bool tipo) {
	tipoOpcion = tipo;
}

tipo_opcion ControladorInterfaz::getOpcionSeleccionada() {
	return this->opcion_seleccionada;
}

void ControladorInterfaz::setOpcionSeleccionada(tipo_opcion opcion) {
	opcion_seleccionada = opcion;
}

map<tipo_opcion, hud*> ControladorInterfaz::getOpciones(int id) {
	switch (id) {
		case 0:
			return opciones_actuales;
			break;
		case 1: 
			return opciones_inicio;
			break;
		case 2:
			return opciones_configuracion;
			break;
	}
	return map<tipo_opcion, hud*>();
}

void ControladorInterfaz::setOpciones(map<tipo_opcion, hud*> opciones, int id) {
	switch (id) {
	case 0:
		opciones_actuales = opciones;
		break;
	case 1:
		opciones_inicio = opciones;
		break;
	case 2:
		opciones_configuracion = opciones;
		break;
	}
}

ControladorInterfaz::~ControladorInterfaz() {
	SDL_FreeSurface(hudPuntaje->mensajeSurface);
	SDL_FreeSurface(hudPuntaje->colorSurface);
	SDL_FreeSurface(hudTiempo->mensajeSurface);
	SDL_FreeSurface(hudTiempo->colorSurface);
	SDL_FreeSurface(hudGameOver->mensajeSurface);
	SDL_FreeSurface(hudGameOver->colorSurface);
	SDL_FreeSurface(hudNivel->mensajeSurface);
	SDL_FreeSurface(hudNivel->colorSurface);
	SDL_FreeSurface(hudEnemigos->mensajeSurface);
	SDL_FreeSurface(hudEnemigos->colorSurface);


	for (pair<const tipo_poder, hud*>& kv : poderes) {
		SDL_FreeSurface(kv.second->mensajeSurface);
		SDL_FreeSurface(kv.second->colorSurface);
		delete kv.second;
	}

	TTF_CloseFont(interfaz);
}


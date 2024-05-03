#include "../lib/ControladorInterfaz.h"

TTF_Font* ControladorInterfaz::interfaz = nullptr;
hud* ControladorInterfaz::hudPuntaje = nullptr;
hud* ControladorInterfaz::hudTiempo = nullptr;
hud* ControladorInterfaz::hudGameOver = nullptr;
list<hudPoder> ControladorInterfaz::poderes = list<hudPoder>();

float const MARGEN_HUD = 10.f * WINDOW_RATIO;
float MARGEN_PODERES = 30.f * WINDOW_RATIO;
float posXPoder = MARGEN_HUD;

void ControladorInterfaz::setPuntaje(int puntos) {
	setMensajeEnComponente("Puntaje: " + to_string(puntaje), interfaz, hudPuntaje);
}

void ControladorInterfaz::setTiempo(int tiemp) {
	setMensajeEnComponente("Tiempo: " + to_string(tiemp), interfaz, hudTiempo);
}

void ControladorInterfaz::setFinJuego(bool finJuego) {
	setMensajeEnComponente(finJuego ? "GAME OVER!" : " ", interfaz, hudGameOver);
}

hud* ControladorInterfaz::getHudPoderes(tipo_poder tipo) {
	for (auto it = poderes.begin(); it != poderes.end(); ++it) {
		if (it->poder == tipo) {
			return it->hud;
		}
	} //asumimos que it no puede llegar al final
	return nullptr;
}

void ControladorInterfaz::setHudPoderes(tipo_poder tipo, hud* hud) {
	bool encontrado = false;
	hudPoder hudPoder{};
	for (auto it = poderes.begin(); !encontrado && it != poderes.end(); ++it) {
		if (it->poder == tipo) {
			hudPoder = (*it);
			encontrado = true;
		}
	}
	if(hudPoder.hud != nullptr)
		delete hudPoder.hud;
	hudPoder.hud = hud;
}

void ControladorInterfaz::setPoderes(map<tipo_poder, int> powerUp){
	for (auto it = powerUp.begin(); it != powerUp.end(); ++it) {
		if (ControladorPoderes::poderDependeDeTiempo(it->first)) {
			if(it->second != 0)
			setMensajeEnComponente(to_string(it->second / 1000), interfaz, getHudPoderes(it->first));
		} else {
			string mensaje = to_string(it->second);
			switch (it->first) {
				case tipo_poder::AUMENTAR_CANTIDAD_BOMBAS:
					mensaje = to_string((it->second + 1) - jugador->getCantBomba()); //cant max - cant actual
					break;
			}
			setMensajeEnComponente(mensaje + "x", interfaz, getHudPoderes(it->first));
		}
	}
}

void ControladorInterfaz::setMensajeEnComponente(string mensaje, TTF_Font* fuente, hud* componente) {
	glColor3f(componente->colorMensaje.r, componente->colorMensaje.g, componente->colorMensaje.b);
	if (componente->mensajeSurface != NULL) {
		SDL_FreeSurface(componente->mensajeSurface);
	}
	componente->mensajeSurface = TTF_RenderText_Blended(fuente, mensaje.c_str(), { 255, 255, 255 });
	if (componente->mensajeSurface == NULL) { // no renderiza el texto correctamente
		cerr << "TTF_RenderText error: " << SDL_GetError() << endl;
		return;
	}
	//Generate OpenGL texture
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &(componente->idTextura));
	glBindTexture(GL_TEXTURE_2D, componente->idTextura);

	TTF_SizeText(fuente, mensaje.c_str(), &(componente->width), &(componente->height));

	//Create a surface to the correct size in RGB format, and copy the old image
	if(componente->colorSurface != NULL)
		SDL_FreeSurface(componente->colorSurface);
	componente->colorSurface = SDL_CreateRGBSurface(0, componente->width, componente->height, 32, 0, 0x0000ff00, 0x000000ff, 0xff000000); //el problema puede ser por no destruir la componente antes de crear una nueva?
	if (componente->colorSurface == NULL) {
		cerr << "SDL_CreateRGBSurface() failed: " << SDL_GetError() << endl;
		exit(1);
	}
	SDL_BlitSurface(componente->mensajeSurface, NULL, componente->colorSurface, NULL);

	//Avoid mipmap filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Copy the created image into OpenGL format
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, componente->width, componente->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, componente->colorSurface->pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void ControladorInterfaz::cargarInterfaz() {
	interfaz = TTF_OpenFont("texturas/OpenSans-Regular.ttf", 24);
	if (interfaz == nullptr) {
		cerr << "Error en TTF_OpenFont: " << SDL_GetError() << endl;
		return;
	}

	ControladorInterfaz::hudPuntaje = new hud();
	ControladorInterfaz::hudTiempo = new hud();
	ControladorInterfaz::hudGameOver = new hud();

	for (int i = 0; i < static_cast<int>(tipo_poder::BONIFICADOR_RANDOM); i++) {
		hudPoder hudPoder{};
		hudPoder.hud = nullptr;
		hudPoder.hud = new hud();
		hudPoder.hud->colorMensaje = { 255, 255, 255 };
		hudPoder.hud->posicion = position::bottom_left;
		hudPoder.poder = static_cast<tipo_poder>(i);
		poderes.push_back(hudPoder);
	}

	ControladorInterfaz::hudPuntaje->colorMensaje = { 255, 255, 255 };
	ControladorInterfaz::hudTiempo->colorMensaje = { 255, 255, 255 };
	ControladorInterfaz::hudGameOver->colorMensaje = { 255, 255, 255 };

	ControladorInterfaz::hudPuntaje->posicion = position::top_right;
	ControladorInterfaz::hudTiempo->posicion = position::top_left;
	ControladorInterfaz::hudGameOver->posicion = position::top_center;

	setPuntaje(puntaje);
	setTiempo(tiempoJuego);
	setFinJuego(fin);
	map<tipo_poder, int> pod = ControladorPoderes::obtenerPoderes();
	setPoderes(pod);
}

hud* ControladorInterfaz::getHud(int numero) {
	switch (numero) {
	case 0:
		return hudPuntaje;
	case 1:
		return hudTiempo;
	case 2:
		return hudGameOver;
	}
}

void ControladorInterfaz::setHud(int indice, hud* hud){
	switch (indice) {
	case 0:
		if (hudPuntaje != nullptr)
			delete hudPuntaje;
		hudPuntaje = hud;
		break;
	case 1:
		if (hudTiempo != nullptr)
			delete hudTiempo;
		hudTiempo = hud;
		break;
	case 2:
		if (hudGameOver != nullptr)
			delete hudGameOver;
		hudGameOver = hud;
		break;
	}
}

void ControladorInterfaz::dibujarComponenteHUDPoderes() {
	posXPoder = MARGEN_HUD;
	for (auto it = poderes.begin(); it != poderes.end(); ++it) {
		if (it->poder==AUMENTAR_CANTIDAD_BOMBAS || ControladorPoderes::getValor(it->poder) != 0) {
			//dibujar texto
			if (!ControladorPoderes::poderEsBooleano(it->poder)) {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, it->hud->idTextura);
				glColor3f(it->hud->colorMensaje.r, it->hud->colorMensaje.g, it->hud->colorMensaje.b);

				//mesaje surface es null y marcho
				glBegin(GL_QUADS); {
					glTexCoord2d(0.f, 1.f); glVertex3f(posXPoder, altoPantalla - MARGEN_HUD, 0.f);
					glTexCoord2d(1.f, 1.f); glVertex3f(posXPoder + it->hud->width, altoPantalla - MARGEN_HUD, 0.f);
					glTexCoord2d(1.f, 0.f); glVertex3f(posXPoder + it->hud->width, altoPantalla - MARGEN_HUD - it->hud->height, 0.f);
					glTexCoord2d(0.f, 0.f); glVertex3f(posXPoder, altoPantalla - MARGEN_HUD - it->hud->height, 0.f);
				} glEnd();

				glDisable(GL_TEXTURE_2D);

				posXPoder += it->hud->width;
			}

			//dibujar icono
			glEnable(GL_TEXTURE_2D);
			tipo_textura tipo = ControladorTexturas::getTipoTexturaPoder(it->poder);
			GLuint textura = ControladorTexturas::getTextura(tipo);
			glBindTexture(GL_TEXTURE_2D, textura);
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 1.f); glVertex3f(posXPoder, altoPantalla - MARGEN_HUD - it->hud->height, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(posXPoder + it->hud->height, altoPantalla - MARGEN_HUD - it->hud->height, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(posXPoder + it->hud->height, altoPantalla - MARGEN_HUD, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(posXPoder, altoPantalla - MARGEN_HUD, 0.f);
			}glEnd();
			glDisable(GL_TEXTURE_2D);

			posXPoder += it->hud->height + MARGEN_PODERES;
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
				glTexCoord2d(0.f, 1.f); glVertex3f(MARGEN_HUD, MARGEN_HUD + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(MARGEN_HUD + hud->mensajeSurface->w, MARGEN_HUD + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(MARGEN_HUD + hud->mensajeSurface->w, MARGEN_HUD, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(MARGEN_HUD, MARGEN_HUD, 0.f);
			} glEnd();
			glDisable(GL_TEXTURE_2D);
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
	}
}

void ControladorInterfaz::dibujarHUD() {
	setPuntaje(puntaje);
	setTiempo(tiempoJuego / 1000);
	setFinJuego(finJuego);
	map<tipo_poder, int> pod = ControladorPoderes::obtenerPoderes();
	setPoderes(pod);

	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
	glOrtho(0, largoPantalla, altoPantalla, 0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();

	glPushMatrix();

	dibujarComponenteHUD(hudTiempo);
	dibujarComponenteHUD(hudPuntaje);
	if (finJuego) {
		dibujarComponenteHUD(hudGameOver);
	}

	// BOTTOM

	dibujarComponenteHUDPoderes(); //BOTTOM RIGHT

	glPopMatrix();

	glMatrixMode(GL_PROJECTION); glPopMatrix();
	glMatrixMode(GL_MODELVIEW); glPopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void ControladorInterfaz::liberarMemoria() {
	SDL_FreeSurface(hudPuntaje->mensajeSurface);
	SDL_FreeSurface(hudPuntaje->colorSurface);
	SDL_FreeSurface(hudTiempo->mensajeSurface);
	SDL_FreeSurface(hudTiempo->colorSurface);
	SDL_FreeSurface(hudGameOver->mensajeSurface);
	SDL_FreeSurface(hudGameOver->colorSurface);

	for (auto it = poderes.begin(); it != poderes.end(); ++it) {
		SDL_FreeSurface((it->hud)->mensajeSurface);
		SDL_FreeSurface((it->hud)->colorSurface);
		delete (it->hud);
	}

	TTF_CloseFont(interfaz);
}


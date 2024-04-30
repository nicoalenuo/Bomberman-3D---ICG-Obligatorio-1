#include "../lib/ControladorInterfaz.h"

TTF_Font* ControladorInterfaz::interfaz = nullptr;
hud* ControladorInterfaz::hudPuntaje = nullptr;
hud* ControladorInterfaz::hudTiempo = nullptr;
hud* ControladorInterfaz::hudGameOver = nullptr;
hud* ControladorInterfaz::hudCantBombas = nullptr;
list<hudPoder> ControladorInterfaz::poderes = list<hudPoder>();

void ControladorInterfaz::setPuntaje(int puntos) {
	setMensajeEnComponente("Puntaje: " + to_string(puntaje), interfaz, hudPuntaje);
}

void ControladorInterfaz::setTiempo(int tiemp) {
	setMensajeEnComponente("Tiempo: " + to_string(tiemp), interfaz, hudTiempo);
}

void ControladorInterfaz::setFinJuego(bool finJuego) {
	setMensajeEnComponente(finJuego ? "GAME OVER!" : " ", interfaz, hudGameOver);
}

void ControladorInterfaz::setCantBombas(int cant) {
	setMensajeEnComponente(to_string(cant), interfaz, hudCantBombas);
}

/*
void ControladorInterfaz::setPoderes(list<poder> powerUp){
	hudPoder hudPower{};
	bool encontrado;
	string mensaje = " ";
	for (auto i = poderes.begin(); i != poderes.end(); ++i) {
		hudPower = (*i);
		encontrado = false;
		for (auto it = powerUp.begin(); !encontrado && it != powerUp.end(); ++it) {
			if (static_cast<int>((*it).powerUp) == static_cast<int>(hudPower.poder)) {
				encontrado = true;
				mensaje = to_string((*it).cantidad);
				setMensajeEnComponente(mensaje, interfaz, hudPower.hud);
				poderes.push_back(hudPower);
			}
		}
	}
}*/

void ControladorInterfaz::setMensajeEnComponente(string mensaje, TTF_Font* fuente, hud* componente) {
	glColor3f(componente->colorMensaje.r, componente->colorMensaje.g, componente->colorMensaje.b);
	componente->mensajeSurface = TTF_RenderText_Blended(fuente, mensaje.c_str(), { 255, 255, 255 });
	if (componente->mensajeSurface == NULL) {
		cerr << "TTF_RenderText error: " << SDL_GetError() << endl;
		return;
	}

	//Generate OpenGL texture
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &(componente->idTextura));
	glBindTexture(GL_TEXTURE_2D, componente->idTextura);

	TTF_SizeText(fuente, mensaje.c_str(), &(componente->width), &(componente->height));

	//Create a surface to the correct size in RGB format, and copy the old image
	componente->colorSurface = SDL_CreateRGBSurface(0, componente->width, componente->height, 32, 0, 0x0000ff00, 0x000000ff, 0xff000000);
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
	ControladorInterfaz::hudCantBombas = new hud();

	for (int i = 0; i < static_cast<int>(tipo_poder::BONIFICADOR_RANDOM); i++) {
		hudPoder hudPoder{};
		hudPoder.hud = new hud();
		hudPoder.hud->colorMensaje = { 255, 255, 255 };
		hudPoder.hud->posicion = position::bottom_right;
		hudPoder.poder = static_cast<tipo_poder>(i);
		poderes.push_back(hudPoder);
	}

	ControladorInterfaz::hudPuntaje->colorMensaje = { 255, 255, 255 };
	ControladorInterfaz::hudTiempo->colorMensaje = { 255, 255, 255 };
	ControladorInterfaz::hudGameOver->colorMensaje = { 255, 255, 255 };
	ControladorInterfaz::hudCantBombas->colorMensaje = { 255, 255, 255 };


	ControladorInterfaz::hudPuntaje->posicion = position::top_right;
	ControladorInterfaz::hudTiempo->posicion = position::top_left;
	ControladorInterfaz::hudGameOver->posicion = position::top_center;
	ControladorInterfaz::hudCantBombas->posicion = position::bottom_left;

	setPuntaje(puntaje);
	setTiempo(tiempoJuego);
	setFinJuego(fin);
	setCantBombas(jugador->getMaxBomba());
	//setPoderes(jugador->getPoderes()); //FALTA: Problema en setPoderes, algo pasa que no carga
}


hud* ControladorInterfaz::getHud(int numero) {
	switch (numero) {
	case 0:
		return hudPuntaje;
		break;
	case 1:
		return hudTiempo;
		break;
	case 2:
		return hudGameOver;
		break;
	case 3:
		return hudCantBombas;
		break;
	}
}

void ControladorInterfaz::setHud(int indice, hud* hud){
	switch (indice) {
	case 0:
		hudPuntaje = hud;
		break;
	case 1:
		hudTiempo = hud;
		break;
	case 2:
		hudGameOver = hud;
		break;
	case 3:
		hudCantBombas = hud;
		break;
	}
}

hud* ControladorInterfaz::getHudPoderes(int indice) {
	int aux = 0;
	hudPoder hudPoder{};
	for (auto it = poderes.begin(); aux <= indice && it != poderes.end(); ++it) {
		hudPoder = (*it);
		aux++;
	}
	//asumimos que it no puede llegar al final?
	return hudPoder.hud;
}

void ControladorInterfaz::setHudPoderes(int indice, hud* hud) {
	int aux = 0;
	hudPoder hudPoder{};
	for (auto it = poderes.begin(); aux <= indice && it != poderes.end(); ++it) {
		hudPoder = (*it);
		aux++;
	}
	delete hudPoder.hud;
	hudPoder.hud = hud;
}

void ControladorInterfaz::dibujarComponenteHUDPoderes() {
	hud* hud{};
	GLfloat desplazamiento = 10.f;
	int cant = 1;
	for (auto it = poderes.begin(); it != poderes.end(); ++it) {
		hud = it->hud;
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, it->hud->idTextura);
		glColor3f(hud->colorMensaje.r, hud->colorMensaje.g, hud->colorMensaje.b);
		
		glBegin(GL_QUADS); {
			glTexCoord2d(0.f, 1.f); glVertex3f(largoPantalla - 30.f - hud->mensajeSurface->w, altoPantalla - 3.f - hud->mensajeSurface->h, 0.f);
			glTexCoord2d(1.f, 1.f); glVertex3f(largoPantalla - 30.f, altoPantalla - 3.f - hud->mensajeSurface->h, 0.f);
			glTexCoord2d(1.f, 0.f); glVertex3f(largoPantalla - 30.f, altoPantalla -  3.f, 0.f);
			glTexCoord2d(0.f, 0.f); glVertex3f(largoPantalla - 30.f - hud->mensajeSurface->w, altoPantalla - 3.f, 0.f);
		} glEnd();
		//dibujarTextura(GLUint text) //logo correspondiente a cada poder
		//realmente no es una función, va acá de una
		glDisable(GL_TEXTURE_2D);
		cant++;
	}
}

void ControladorInterfaz::dibujarComponenteHUD(hud* hud) {
	switch (hud->posicion) {
		case position::top_left:
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, hud->idTextura);
			glColor3f(hud->colorMensaje.r, hud->colorMensaje.g, hud->colorMensaje.b);
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 1.f); glVertex3f(30.f, 3.f + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(30.f + hud->mensajeSurface->w, 3.f + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(30.f + hud->mensajeSurface->w, 3.f, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(30.f, 3.f, 0.f);
			} glEnd();
			glDisable(GL_TEXTURE_2D);
			break;
		case position::top_right:
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, hud->idTextura);
			glColor3f(hud->colorMensaje.r, hud->colorMensaje.g, hud->colorMensaje.b);
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 1.f); glVertex3f(largoPantalla - 30.f - hud->mensajeSurface->w, 3.f + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(largoPantalla - 30.f, 3.f + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(largoPantalla - 30.f, 3.f, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(largoPantalla - 30.f - hud->mensajeSurface->w, 3.f, 0.f);
			} glEnd();
			glDisable(GL_TEXTURE_2D);
			break;
		case position::top_center:
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, hud->idTextura);
			glColor3f(hud->colorMensaje.r, hud->colorMensaje.g, hud->colorMensaje.b);
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 1.f); glVertex3f(largoPantalla / 2.f - hud->mensajeSurface->w / 2.f, 3.f + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(largoPantalla / 2.f + hud->mensajeSurface->w / 2.f, 3.f + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(largoPantalla / 2.f + hud->mensajeSurface->w / 2.f, 3.f, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(largoPantalla / 2.f - hud->mensajeSurface->w / 2.f, 3.f, 0.f);
			} glEnd();
			glDisable(GL_TEXTURE_2D);
			break;
		case position::bottom_left: //cant de bombas disponibles
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, hud->idTextura);
			glColor3f(hud->colorMensaje.r, hud->colorMensaje.g, hud->colorMensaje.b);
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 0.f); glVertex3f(30.f, altoPantalla - 3.f - hud->mensajeSurface->h, 0.f);
				glTexCoord2d(0.f, 1.f); glVertex3f(30.f, altoPantalla - 3.f, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(30.f + hud->mensajeSurface->w, altoPantalla - 3.f, 0.f); 
				glTexCoord2d(1.f, 0.f); glVertex3f(30.f + hud->mensajeSurface->w, altoPantalla - 3.f - hud->mensajeSurface->h, 0.f);
			} glEnd();
			glDisable(GL_TEXTURE_2D);

			//dibujar el ícono de aumentar cantidad de bombas (al inicio es 1)
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, ControladorTexturas::getTextura(TEXTURA_AUMENTAR_CANTIDAD_BOMBA));
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 0.f); glVertex3f(30.f + hud->mensajeSurface->w, altoPantalla - 3.f, 0.f);
				glTexCoord2d(0.f, 1.f); glVertex3f(30.f + hud->mensajeSurface->w, altoPantalla - 3.f - hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(30.f + hud->mensajeSurface->w + hud->mensajeSurface->h, altoPantalla - 3.f - hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(30.f + hud->mensajeSurface->w + hud->mensajeSurface->h, altoPantalla - 3.f, 0.f);
			}glEnd();
			glDisable(GL_TEXTURE_2D);
			break;
	}
}

void ControladorInterfaz::dibujarHUD() {
	setPuntaje(puntaje);
	setTiempo(tiempoJuego);
	setFinJuego(finJuego);
	setCantBombas(jugador->getMaxBomba() - jugador->getCantBomba());

	glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
	glOrtho(0, largoPantalla, altoPantalla, 0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();

	glPushMatrix();

	// TOP
	int height = max(hudPuntaje->height, hudTiempo->height);
	dibujarComponenteHUD(hudTiempo);
	dibujarComponenteHUD(hudPuntaje);
	if (finJuego) {
		dibujarComponenteHUD(hudGameOver);
	}

	// BOTTOM

	dibujarComponenteHUD(hudCantBombas); //BOTTOM LEFT

	//dibujarComponenteHUDPoderes(); //BOTTOM RIGHT

	glPopMatrix();

	glMatrixMode(GL_PROJECTION); glPopMatrix();
	glMatrixMode(GL_MODELVIEW); glPopMatrix();
}


#include "../lib/ControladorInterfaz.h"

TTF_Font* ControladorInterfaz::interfaz = nullptr;
hud* ControladorInterfaz::puntaje = nullptr;
hud* ControladorInterfaz::tiempo = nullptr;
hud* ControladorInterfaz::gameOver = nullptr;

void ControladorInterfaz::setPuntaje(int puntos) {
	string mensaje = "Puntaje: " + to_string(puntos);
	setMensajeEnComponente(mensaje, interfaz, puntaje);
}

void ControladorInterfaz::setTiempo(int tiemp) {
	string mensaje = "Tiempo: " + to_string(tiemp);
	setMensajeEnComponente(mensaje, interfaz, tiempo);
}

void ControladorInterfaz::setFinJuego(bool finJuego) {
	string mensaje;
	if (finJuego) {
		mensaje = "GAME OVER!";
	} else {
		mensaje = " ";
	}
	setMensajeEnComponente(mensaje, interfaz, gameOver);
}

void ControladorInterfaz::actualizarInterfaz(int puntos, int tiemp, bool finJuego){
	setPuntaje(puntos);
	setTiempo(tiemp);
	setFinJuego(finJuego);
}

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

void ControladorInterfaz::cargarInterfaz(int puntaje, int tiempo, bool fin) {

	if (TTF_Init() < 0) {
		cerr << "[SDL TTF Error]: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}

	interfaz = TTF_OpenFont("texturas/OpenSans-Regular.ttf", 24);
	if (interfaz == nullptr) {
		cerr << "TTF_OpenFont error: " << SDL_GetError() << endl;
		return;
	}

	ControladorInterfaz::puntaje = new hud();
	ControladorInterfaz::tiempo = new hud();
	ControladorInterfaz::gameOver = new hud();

	ControladorInterfaz::puntaje->colorMensaje = { 255, 255, 255 };
	ControladorInterfaz::tiempo->colorMensaje = { 255, 255, 255 };
	ControladorInterfaz::gameOver->colorMensaje = { 255, 255, 255 };

	ControladorInterfaz::puntaje->posicion = position::top_right;
	ControladorInterfaz::tiempo->posicion = position::top_left;
	ControladorInterfaz::gameOver->posicion = position::top_center;

	setPuntaje(puntaje);
	setTiempo(tiempo);
	setFinJuego(fin);
}


hud* ControladorInterfaz::getHud(int numero) {
	switch (numero) {
	case 0:
		return puntaje;
		break;
	case 1:
		return tiempo;
		break;
	default:
		return gameOver;
		break;
	}
}

void ControladorInterfaz::setHud(int indice, hud* hud){
	switch (indice) {
	case 0:
		puntaje = hud;
		break;
	case 1:
		tiempo = hud;
		break;
	default:
		gameOver = hud;
		break;
	}
}

void ControladorInterfaz::dibujarCompomenteHUD(hud* hud) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, hud->idTextura);
	glColor3f(hud->colorMensaje.r, hud->colorMensaje.g, hud->colorMensaje.b);
	switch (hud->posicion) {
		case position::top_left:
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 1.f); glVertex3f(30.f, 3.f + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(30.f + hud->mensajeSurface->w, 3.f + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(30.f + hud->mensajeSurface->w, 3.f, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(30.f, 3.f, 0.f);
			} glEnd();
		break;
		case position::top_right:
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 1.f); glVertex3f(WINDOW_WIDTH - 30.f - hud->mensajeSurface->w, 3.f + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(WINDOW_WIDTH - 30.f, 3.f + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(WINDOW_WIDTH - 30.f, 3.f, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(WINDOW_WIDTH - 30.f - hud->mensajeSurface->w, 3.f, 0.f);
			} glEnd();
		break;
		case position::top_center:
			glBegin(GL_QUADS); {
				glTexCoord2d(0.f, 1.f); glVertex3f(WINDOW_WIDTH / 2.f - hud->mensajeSurface->w / 2.f, 3.f + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 1.f); glVertex3f(WINDOW_WIDTH / 2.f + hud->mensajeSurface->w / 2.f, 3.f + hud->mensajeSurface->h, 0.f);
				glTexCoord2d(1.f, 0.f); glVertex3f(WINDOW_WIDTH / 2.f + hud->mensajeSurface->w / 2.f, 3.f, 0.f);
				glTexCoord2d(0.f, 0.f); glVertex3f(WINDOW_WIDTH / 2.f - hud->mensajeSurface->w / 2.f, 3.f, 0.f);
			} glEnd();
		break;
	}
	glDisable(GL_TEXTURE_2D);
}

void ControladorInterfaz::dibujarHUD() {
	glPushMatrix();

	// TOP
	int height = max(puntaje->height, tiempo->height);
	dibujarCompomenteHUD(tiempo);
	dibujarCompomenteHUD(puntaje);
	dibujarCompomenteHUD(gameOver);

	// El Resto
	// Draw the rest of the overlay
	/*
	glBegin(GL_QUADS); {
		glColor3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, height + 6.f, 0.f);
		glVertex3f(WINDOW_WIDTH, height + 6.f, 0.f);
		glVertex3f(WINDOW_WIDTH, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
	} glEnd();
	*/

	// BOTTOM

	// dibujar los poderes
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, ...);
	glBegin(GL_QUADS); {
		glColor3f(1.f,1.f,1.f);
		//glTexCoord2d(0.f, 1.f); 
		glVertex3f(0.f, WINDOW_HEIGHT - 62.f, 1.f);
		//glTexCoord2d(1.f, 1.f);
		glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT - 62.f, 1.f);
		//glTexCoord2d(1.f, 0.f);
		glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 1.f);
		//glTexCoord2d(0.f, 0.f);
		glVertex3f(0.f, WINDOW_HEIGHT, 1.f);
	} glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


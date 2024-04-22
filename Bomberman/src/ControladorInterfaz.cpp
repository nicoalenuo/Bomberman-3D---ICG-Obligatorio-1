#include "../lib/ControladorInterfaz.h"

void ControladorInterfaz::setMensajeEnComponente(string mensaje, TTF_Font* fuente, hud* componente) {
	glColor3f(componente->colorMensaje.r, componente->colorMensaje.g, componente->colorMensaje.b);
	componente->mensajeSurface = TTF_RenderText_Blended(fuente, mensaje.c_str(), {255, 255, 255});
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
	/*
	interfaz = TTF_OpenFont("texturas/OpenSans-Regular.ttf", 24);
	if (interfaz == nullptr) {
		cerr << "TTF_OpenFont error: " << SDL_GetError() << endl;
		return;
	}

	hud* puntaje = new hud();
	hud* tiempo = new hud();
	hud* gameOver = new hud();
	puntaje->colorMensaje = { 255, 255, 255 };
	tiempo->colorMensaje = { 255, 255, 255 };
	gameOver->colorMensaje = { 255, 255, 255 };

	puntaje->posicion = position::top_left;
	tiempo->posicion = position::top_right;
	gameOver->posicion = position::top_center;

	setPuntaje(0);
	setTiempo(200);
	setFinJuego(false);*/
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

void ControladorInterfaz::setPuntaje(int puntos) {
	string message = "Score: " + to_string(puntos);
	setMensajeEnComponente(message, interfaz, puntaje);
}

void ControladorInterfaz::setTiempo(int tiemp) {
	string message = "Coins: " + to_string(tiemp);
	setMensajeEnComponente(message, interfaz, tiempo);
}

void ControladorInterfaz::setFinJuego(bool finJuego) {
	string message;
	if (finJuego) {
		message = "GAME OVER!";
	} else {
		message = "  ";
	}
	setMensajeEnComponente(message, interfaz, gameOver);
}
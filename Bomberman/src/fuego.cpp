#include "../lib/fuego.h"
#include "../lib/controlador.h"

fuego::fuego(posicion pos, tamanio tam, int tiempo) : objeto(pos, tam) {
	tiempoFuego = tiempo;

	cout << pos.x << " " << pos.z << endl;
}

void fuego::actualizar() {
	tiempoFuego -= frameDelay;

	if (tiempoFuego <= 0) {
		Controlador* controlador = Controlador::getInstance();
		objeto*** fuegos = controlador->getFuegos();
		int x = controlador->getPosicionXEnTablero(pos.x, tam.x);
		int z = controlador->getPosicionZEnTablero(pos.z, tam.z);

		fuegos[x][z] = nullptr;
		delete this;
	}
}

void fuego::dibujar() {
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(tam.x, 0, 0);
	glVertex3f(tam.x, 0, tam.z);
	glVertex3f(0, 0, tam.z);
	glEnd();

	glPopMatrix();
}

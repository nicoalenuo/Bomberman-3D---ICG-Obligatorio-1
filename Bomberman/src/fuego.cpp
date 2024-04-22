#include "../lib/fuego.h"

fuego::fuego(posicion pos, tamanio tam, int tiempo) : objeto(pos, tam) {
	tiempoFuego = tiempo;
}

void fuego::actualizar() {
	tiempoFuego -= frameDelay;

	if (tiempoFuego <= 0) {
		int x = getPosicionXEnTablero(pos.x, tam.x);
		int z = getPosicionZEnTablero(pos.z, tam.z);

		fuegos[x][z] = nullptr;
		delete this;
	}
}

void fuego::dibujar() {
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-tam.x, 0, -tam.z);
	glVertex3f(tam.x, 0, -tam.z);
	glVertex3f(tam.x, 0, tam.z);
	glVertex3f(-tam.x, 0, tam.z);
	glEnd();

	glPopMatrix();
}

#include "../lib/fuego.h"

fuego::fuego(vector_3 pos, vector_3 tam, int tiempo) : objeto(pos, tam) {
	tiempoFuego = tiempo;
}

void fuego::actualizar() {
	tiempoFuego -= frameDelay;

	if (tiempoFuego <= 0) {
		int x = getPosicionXEnTablero(pos.x);
		int z = getPosicionZEnTablero(pos.z);

		fuegos[x][z] = nullptr;
		delete this;
	}
}

void fuego::dibujar() {
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-tam.x, 0, -tam.z);
	glVertex3f(tam.x, 0, -tam.z);
	glVertex3f(tam.x, 0, tam.z);
	glVertex3f(-tam.x, 0, tam.z);
	glEnd();

	glPopMatrix();
}

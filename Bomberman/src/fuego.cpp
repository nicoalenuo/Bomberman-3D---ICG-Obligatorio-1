#include "../lib/fuego.h"

fuego::fuego(vector_3 pos, vector_3 tam, int tiempo) : objeto(pos, tam) {
	tiempoFuego = tiempo;
}

int x, z;
void fuego::actualizar() {
	tiempoFuego -= frameDelay;
	x = getPosicionXEnTablero(pos.x);
	z = getPosicionZEnTablero(pos.z);

	if (bombas[x][z] != nullptr) 
		dynamic_cast<bomba*>(bombas[x][z])->setTiempoBomba(0);

	if (bonificadores[x][z] != nullptr) {
		bonificadores[x][z] = nullptr;
		delete bonificadores[x][z];
	}
	if (tiempoFuego <= 0) {
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

#include "../lib/interfazJuego.h"

interfazJuego* interfazJuego::instancia = nullptr;

interfazJuego::interfazJuego() {
	this->visible = true;
}

bool interfazJuego::getVisible() {
	return this->visible;
}

void interfazJuego::setVisible(bool visible) {
	this->visible = visible;
}

void interfazJuego::swapVisible() {
	this->visible = !this->visible;
}

void interfazJuego::dibujar() {
	if (this->visible) {
		//Probablemente cambie la ubicacion
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(-20., 20., -20., 20.);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glBegin(GL_QUADS);
		glColor4f(0.f, 0.f, 0.f, 0.5f);
		glVertex3f(12.f, 8.f, 1.f);
		glVertex3f(20.f, 8., 1.f);
		glVertex3f(20.f, -8.f, 1.f);
		glVertex3f(12.f, -8.f, 1.f);
		glEnd();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
}

interfazJuego* interfazJuego::getInstance() {
	if (instancia == nullptr) {
		instancia = new interfazJuego();
	}
	return instancia;
}

interfazJuego::~interfazJuego() {};


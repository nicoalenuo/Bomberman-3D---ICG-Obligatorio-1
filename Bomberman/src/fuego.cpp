#include "../lib/fuego.h"

fuego::fuego(vector_3 pos, vector_3 tam, int tiempo, bool centro) : objeto(pos, tam) {
	tiempoFuego = tiempo;
	this->centro = centro;
}

random_device rdParticulaFuego;
mt19937 genParticulaFuego(rdParticulaFuego());
uniform_real_distribution<> disParticulaFuego(-tile_size/2, tile_size/2);
uniform_real_distribution<> disParticulaFuegoVelocidad(-0.03, 0.03);
int x, z;
void fuego::actualizar() {
	if (centro) {
		GLfloat colorLuz[4] = { 1.0f, 0.0f, 0.0f, 0.1f };
		ControladorLuz::pedirLuz(pos, colorLuz);
	}

	tiempoFuego -= int(elapsed_time);
	x = getIndiceTablero(pos.x);
	z = getIndiceTablero(pos.z);

	if (bombas[x][z] != nullptr) 
		dynamic_cast<bomba*>(bombas[x][z])->setTiempoBomba(0);

	if (!ControladorPoderes::getEstaActivo(BOMBAS_ATRAVIESAN_ESTRUCTURAS) && bonificadores[x][z] != nullptr) {
		delete bonificadores[x][z];
		bonificadores[x][z] = nullptr;
	}

	for (int j = 0; j < 40; j++) {
		particulas.push_back(
			new particula_fuego(
				{ GLfloat(pos.x + disParticulaFuego(genParticulaFuego)), 0.0f, GLfloat(pos.z + disParticulaFuego(genParticulaFuego)) },
				{ GLfloat(0.04), GLfloat(0.1), GLfloat(0.04) },
				{ 0.0f, GLfloat(10.0f + disParticulaFuego(genParticulaFuego)), 0.0f },
				{ GLfloat(disParticulaFuegoVelocidad(genParticulaFuego)), 0, GLfloat(disParticulaFuegoVelocidad(genParticulaFuego)) }
			)
		);
	}

	if (tiempoFuego <= 0) {
		fuegos[x][z] = nullptr;
		delete this;
	}
}

void fuego::dibujar() {

}

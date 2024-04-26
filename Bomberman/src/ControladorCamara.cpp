#include "../lib/ControladorCamara.h"

tipo_camara ControladorCamara::camara_actual = CAMARA_ISOMETRICA;
int ControladorCamara::tiempoSacudirse = 0;

void ControladorCamara::cambiarTipoCamara() {
	switch (camara_actual) {
		case CAMARA_ISOMETRICA:
			camara_actual = CAMARA_PRIMERA_PERSONA;
			break;
		default:
		case CAMARA_PRIMERA_PERSONA:
			camara_actual = CAMARA_TERCERA_PERSONA;
			break;
		case CAMARA_TERCERA_PERSONA:
			camara_actual = CAMARA_ISOMETRICA;
			break;
	}
}

void ControladorCamara::sacudir(int tiempo) {
	tiempoSacudirse = tiempo;
}

random_device rdSacudirse;
mt19937 genSacudirse(rdSacudirse());
uniform_real_distribution<> disSacudirseIsometrica(-0.2, 0.2);
uniform_real_distribution<> disSacudirsePrimeraPersona(-0.03, 0.03);

GLfloat angleRadiansX, angleRadiansY, camX, camY, camZ;
void ControladorCamara::colocarCamara() {

	if (tiempoSacudirse > 0)
		tiempoSacudirse -= frameDelay * velocidad_juego;

	switch (camara_actual) {
		case CAMARA_ISOMETRICA:
		default:
			angleRadiansX = mouseX * radians;

			camX = (*jugador).getPosicion().x + 20.0f * sin(angleRadiansX);
			camZ = (*jugador).getPosicion().z + 20.0f * cos(angleRadiansX);

			gluLookAt(camX, 30, camZ, 
				(*jugador).getPosicion().x + (tiempoSacudirse > 0 ? GLfloat(disSacudirseIsometrica(genSacudirse)) : 0), 
				(*jugador).getPosicion().y, 
				(*jugador).getPosicion().z + (tiempoSacudirse > 0 ? GLfloat(disSacudirseIsometrica(genSacudirse)) : 0),
				0, 1, 0
			);
			break;
		case CAMARA_PRIMERA_PERSONA:
			angleRadiansX = ((mouseX + 180) % 360) * radians;

			camX = sin(angleRadiansX);
			camZ = cos(angleRadiansX);

			gluLookAt(jugador->getPosicion().x, 3.5f, jugador->getPosicion().z,
				jugador->getPosicion().x + camX + (tiempoSacudirse > 0 ? GLfloat(disSacudirsePrimeraPersona(genSacudirse)) : 0),
				(mouseY / 40.0f) + 2.5f + (tiempoSacudirse > 0 ? GLfloat(disSacudirsePrimeraPersona(genSacudirse)) : 0),
				jugador->getPosicion().z + camZ + (tiempoSacudirse > 0 ? GLfloat(disSacudirsePrimeraPersona(genSacudirse)) : 0),
				0.0f, 1.0f, 0.0f);  

			break;
		case CAMARA_TERCERA_PERSONA:
			angleRadiansX = mouseX * radians;
			angleRadiansY = mouseY * radians;

			camX = jugador->getPosicion().x + 10.0f * sin(angleRadiansX);
			camY = jugador->getPosicion().y + 10.0f * sin(angleRadiansY);
			camZ = jugador->getPosicion().z + 10.0f * cos(angleRadiansX);

			gluLookAt(camX, camY, camZ,
				jugador->getPosicion().x,
				jugador->getPosicion().y,
				jugador->getPosicion().z,
				0, 1, 0);
			break;
		case CAMARA_ORIGINAL:
			break;

	}
}
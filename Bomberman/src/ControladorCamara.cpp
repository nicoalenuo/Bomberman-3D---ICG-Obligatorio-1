#include "../lib/ControladorCamara.h"

tipo_camara ControladorCamara::camara_actual = CAMARA_ISOMETRICA;

void ControladorCamara::cambiarTipoCamara(tipo_camara camara) {
	ControladorCamara::camara_actual = camara;
}

GLfloat angleRadians, camX, camZ;
void ControladorCamara::colocarCamara() {
	switch (camara_actual) {
		case CAMARA_ISOMETRICA:
		default:
			angleRadians = mouseX * radians;

			camX = (*jugador).getPosicion().x + 20.0f * sin(angleRadians);
			camZ = (*jugador).getPosicion().z + 20.0f * cos(angleRadians);

			gluLookAt(camX, 30, camZ, (*jugador).getPosicion().x, 0, (*jugador).getPosicion().z, 0, 1, 0);
			break;
		case CAMARA_TERCERA_PERSONA:
			break;

		case CAMARA_ORIGINAL:
			break;

	}
}
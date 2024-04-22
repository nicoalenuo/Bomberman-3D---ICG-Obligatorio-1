#include "../lib/ControladorCamara.h"

tipo_camara ControladorCamara::camara_actual = CAMARA_ISOMETRICA;

void ControladorCamara::cambiarTipoCamara(tipo_camara camara) {
	ControladorCamara::camara_actual = camara;
}

GLfloat angleRadiansX, angleRadiansY, camX, camY, camZ;
float angleHorizontal;
void ControladorCamara::colocarCamara() {
	switch (camara_actual) {
		case CAMARA_ISOMETRICA:
		default:
			angleRadiansX = mouseX * radians;

			camX = (*jugador).getPosicion().x + 20.0f * sin(angleRadiansX);
			camZ = (*jugador).getPosicion().z + 20.0f * cos(angleRadiansX);

			gluLookAt(camX, 30, camZ, 
				(*jugador).getPosicion().x, (*jugador).getPosicion().y, (*jugador).getPosicion().z, 
				0, 1, 0
			);
			break;
        case CAMARA_TERCERA_PERSONA:
			angleHorizontal = ((mouseX + 90) % 360) * radians;
			gluLookAt((*jugador).getPosicion().x, 1.5, (*jugador).getPosicion().z,
				(*jugador).getPosicion().x + cos(angleHorizontal), 1, (*jugador).getPosicion().z + sin(angleHorizontal),
				0.0f, 1.0f, 0.0f);
            
            break;
		case CAMARA_ORIGINAL:
			break;

	}
}
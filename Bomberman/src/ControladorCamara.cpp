#include "../lib/ControladorCamara.h"

tipo_camara ControladorCamara::camara_actual = CAMARA_ISOMETRICA;
int ControladorCamara::tiempoSacudirse = 0;

void ControladorCamara::cambiarTipoCamara(tipo_camara camara) {
	ControladorCamara::camara_actual = camara;
}

void ControladorCamara::sacudir(int tiempo) {
	tiempoSacudirse = tiempo;
}


random_device rdSacudirse;
mt19937 genSacudirse(rdSacudirse());
uniform_real_distribution<> disSacudirse(-0.2, 0.2);

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
				(*jugador).getPosicion().x + (tiempoSacudirse > 0 ? GLfloat(disSacudirse(genSacudirse)) : 0), 
				(*jugador).getPosicion().y, 
				(*jugador).getPosicion().z + (tiempoSacudirse > 0 ? GLfloat(disSacudirse(genSacudirse)) : 0),
				0, 1, 0
			);
			break;
        case CAMARA_TERCERA_PERSONA:
            
            break;
		case CAMARA_ORIGINAL:
			break;

	}
}
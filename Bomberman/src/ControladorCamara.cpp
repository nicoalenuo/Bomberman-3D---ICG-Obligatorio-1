#include "../lib/ControladorCamara.h"

tipo_camara ControladorCamara::camara_actual = CAMARA_ISOMETRICA;
int ControladorCamara::tiempoSacudirse = 0;

void ControladorCamara::cambiarTipoCamara() {
	camara_actual = tipo_camara((int(camara_actual) + 1) % 3);
}

bool ControladorCamara::camaraMiraHacia(tipo_direccion direccion) {
	switch (direccion) {
		case EJE_X:
			return mouseX >= 225 && mouseX < 315;
			break;
		case EJE_Z:
			return mouseX >= 135 && mouseX < 225;
			break;
		case EJE_MENOS_X:
			return mouseX >= 45 && mouseX < 135;
			break;
		case EJE_MENOS_Z:
			return mouseX >= 315 && mouseX < 45;
			break;
		default:
			return false;
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

void ControladorCamara::colocarCamara(vector_3 pos) {
	if (tiempoSacudirse > 0)
		tiempoSacudirse -= int(elapsed_time);

	switch (camara_actual) {
		case CAMARA_ISOMETRICA:
			angleRadiansX = mouseX * radians;

			camX = pos.x + 20.0f * sin(angleRadiansX);
			camZ = pos.z + 20.0f * cos(angleRadiansX);

			gluLookAt(camX, 30, camZ,
				pos.x + (tiempoSacudirse > 0 ? GLfloat(disSacudirseIsometrica(genSacudirse)) : 0), 
				pos.y, 
				pos.z + (tiempoSacudirse > 0 ? GLfloat(disSacudirseIsometrica(genSacudirse)) : 0),
				0, 1, 0
			);
			break;
		case CAMARA_PRIMERA_PERSONA:
			angleRadiansX = GLfloat(fmod(mouseX + 180, 360)) * radians;

			camX = sin(angleRadiansX);
			camZ = cos(angleRadiansX);

			gluLookAt(pos.x, 3.5f, pos.z,
				pos.x + camX + (tiempoSacudirse > 0 ? GLfloat(disSacudirsePrimeraPersona(genSacudirse)) : 0),
				(mouseY / 40.0f) + 2.5f + (tiempoSacudirse > 0 ? GLfloat(disSacudirsePrimeraPersona(genSacudirse)) : 0),
				pos.z + camZ + (tiempoSacudirse > 0 ? GLfloat(disSacudirsePrimeraPersona(genSacudirse)) : 0),
				0.0f, 1.0f, 0.0f);  

			break;
		case CAMARA_TERCERA_PERSONA:
			angleRadiansX = mouseX * radians;
			angleRadiansY = mouseY_invertido * radians;

			camX = pos.x + 10.0f * sin(angleRadiansX);
			camY = pos.y + 10.0f * sin(angleRadiansY);
			camZ = pos.z + 10.0f * cos(angleRadiansX);

			gluLookAt(camX, camY, camZ,
				pos.x,
				pos.y,
				pos.z,
				0, 1, 0);
			break;
	}
}
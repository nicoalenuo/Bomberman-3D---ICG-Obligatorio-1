#include "../lib/ControladorCamara.h"

ControladorCamara* ControladorCamara::instancia = nullptr;

ControladorCamara* ControladorCamara::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorCamara();
	return instancia;
}

ControladorCamara::ControladorCamara() {
	camara_actual = CAMARA_ISOMETRICA;
	tiempoSacudirse = 0;

	valores_camara = { 0.0f, 45.0f, 0.0f };
	camara_centro = { 0.0f, 0.0f, 0.0f };
	camara_direccion = { 0.0f, 0.0f, 0.0f };
	distancia_a_jugador = 20.0f;
}

void ControladorCamara::cambiarTipoCamara() {
	camara_actual = tipo_camara((int(camara_actual) + 1) % 3);
	valores_camara.y = 45.0f;
}

bool ControladorCamara::camaraMiraHacia(tipo_direccion direccion) {
	switch (direccion) {
		case EJE_X:
			return valores_camara.x >= 225 && valores_camara.x < 315;
			break;
		case EJE_Z:
			return valores_camara.x >= 135 && valores_camara.x < 225;
			break;
		case EJE_MENOS_X:
			return valores_camara.x >= 45 && valores_camara.x < 135;
			break;
		case EJE_MENOS_Z:
			return valores_camara.x >= 315 && valores_camara.x < 45;
			break;
		default:
			return false;
	}
}

void ControladorCamara::actualizarValoresMouse(GLfloat diferencia_x, GLfloat diferencia_y) {
	valores_camara.x = GLfloat(fmod(valores_camara.x - (diferencia_x * SENSIBILIDAD_MOUSE), 360));
	if (valores_camara.x < 0)
		valores_camara.x += 360;

	valores_camara.y = valores_camara.y - (diferencia_y * SENSIBILIDAD_MOUSE);
	if (valores_camara.y < 5.0f)
		valores_camara.y = 5.0f;
	else if (valores_camara.y > 90.0f)
		valores_camara.y = 90.0f;
}

void ControladorCamara::actualizarValoresRueda(GLfloat diferencia_rueda) {
	distancia_a_jugador -= diferencia_rueda;
	if (distancia_a_jugador < 5.f) {
		distancia_a_jugador = 5.0f;
	}
	if (distancia_a_jugador > 40.0f) {
		distancia_a_jugador = 40.0f;
	}
}

void ControladorCamara::sacudir(int tiempo) {
	tiempoSacudirse = tiempo;
}

random_device rdSacudirse;
mt19937 genSacudirse(rdSacudirse());
uniform_real_distribution<> disSacudirseIsometrica(-0.2, 0.2);
uniform_real_distribution<> disSacudirsePrimeraPersona(-0.03, 0.03);

void ControladorCamara::colocarCamara(vector_3 pos) {
	GLfloat angleRadiansX, angleRadiansY;
	if (tiempoSacudirse > 0)
		tiempoSacudirse -= int(tiempo_entre_frames);

	switch (camara_actual) {
		case CAMARA_ISOMETRICA:
			angleRadiansX = valores_camara.x * radians;

			camara_centro.x = pos.x + distancia_a_jugador * sin(angleRadiansX);
			camara_centro.y = 30;
			camara_centro.z = pos.z + distancia_a_jugador * cos(angleRadiansX);

			camara_direccion.x = pos.x + (tiempoSacudirse > 0 ? GLfloat(disSacudirseIsometrica(genSacudirse)) : 0);
			camara_direccion.y = pos.y;
			camara_direccion.z = pos.z + (tiempoSacudirse > 0 ? GLfloat(disSacudirseIsometrica(genSacudirse)) : 0);

			break;
		case CAMARA_PRIMERA_PERSONA:
			angleRadiansX = GLfloat(fmod(valores_camara.x + 180, 360)) * radians;

			camara_centro.x = pos.x;
			camara_centro.y = 3.5f;
			camara_centro.z = pos.z;

			camara_direccion.x = sin(angleRadiansX) + pos.x + (tiempoSacudirse > 0 ? GLfloat(disSacudirsePrimeraPersona(genSacudirse)) : 0);
			camara_direccion.y = (valores_camara.y / 40.0f) + 2.5f + (tiempoSacudirse > 0 ? GLfloat(disSacudirsePrimeraPersona(genSacudirse)) : 0);
			camara_direccion.z = cos(angleRadiansX) + pos.z + (tiempoSacudirse > 0 ? GLfloat(disSacudirsePrimeraPersona(genSacudirse)) : 0);

			break;
		case CAMARA_TERCERA_PERSONA:
			angleRadiansX = valores_camara.x * radians;
			angleRadiansY = valores_camara.y * radians;


			camara_centro.x = pos.x + distancia_a_jugador * sin(angleRadiansX) * sin(angleRadiansY);
			camara_centro.y = pos.y + distancia_a_jugador * cos(angleRadiansY);
			camara_centro.z = pos.z + distancia_a_jugador * cos(angleRadiansX) * sin(angleRadiansY);

			camara_direccion.x = pos.x + (tiempoSacudirse > 0 ? GLfloat(disSacudirseIsometrica(genSacudirse)) : 0);
			camara_direccion.y = pos.y + tile_size;
			camara_direccion.z = pos.z + (tiempoSacudirse > 0 ? GLfloat(disSacudirseIsometrica(genSacudirse)) : 0);

			break;
	}

	gluLookAt(
		camara_centro.x, camara_centro.y, camara_centro.z,
		camara_direccion.x, camara_direccion.y, camara_direccion.z,
		0, 1, 0
	);
}

ControladorCamara::~ControladorCamara() {

}
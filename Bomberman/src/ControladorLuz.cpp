#include "../lib/ControladorLuz.h"

// DEJEN COMENTADO ESTO PQ ME OLVIDO LOS ENUMS Y NO QUIERO IR AL .h
// enum TIPO_LUZ_AMBIENTE { MANIANA, TARDE, NOCHE, SIN_LUZ };
// enum TIPO_LUZ_BONIFICADOR { AMARILLO, CELESTE, VIOLETA, SIN_LUZ };


TIPO_LUZ_AMBIENTE ControladorLuz::colorLuzAmbiente = MANIANA;
TIPO_LUZ_BONIFICADOR ControladorLuz::colorLuzBonificador = AMARILLO;
GLfloat ControladorLuz::light_position[4] = { 0, 0, 0, 1 };
GLfloat ControladorLuz::light_color[4] = { 1, 1, 1, 1 };
GLfloat ControladorLuz::material_ambient_diffuse_color[4] = { 1, 1, 1, 1 };
GLfloat ControladorLuz::material_specular_color[4] = { 0, 1, 0, 1 };
GLfloat ControladorLuz::light_offset_x = 0.f;
GLfloat ControladorLuz::light_offset_y = 50.f;
GLfloat ControladorLuz::light_offset_z = 0.f;


void ControladorLuz::colocarLuces() {
	if (texturas_habilitadas) {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0); 
		light_position[0] = jugador->getPosicion().x + light_offset_x;
		light_position[1] = jugador->getPosicion().y + light_offset_y;
		light_position[2] = jugador->getPosicion().z + light_offset_z;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
	}
}

void ControladorLuz::cambiarColorLuzAmbiente() {
	int luzActual = static_cast<int>(colorLuzAmbiente);
	luzActual = (luzActual + 1) % 4;
	colorLuzAmbiente = TIPO_LUZ_AMBIENTE(luzActual);
	switch (luzActual) {
		case 0:
			light_color[0] = 0.8f; light_color[1] = 0.8f; light_color[2] = 0.2f;
			break;
		case 1:
			light_color[0] = 0.8f; light_color[1] = 0.4f; light_color[2] = 0.2f;
			break;
		case 2:
			light_color[0] = 0.f; light_color[1] = 0.2f; light_color[2] = 0.5f;
			break;
		case 3:
			light_color[0] = 1.f; light_color[1] = 1.f; light_color[2] = 1.f;
			break;
	}
}

void ControladorLuz::cambiarColorLuzBonificador() {
	int luzActual = static_cast<int>(colorLuzBonificador);
	luzActual = (luzActual + 1) % 4;
	colorLuzBonificador = TIPO_LUZ_BONIFICADOR (luzActual);
	switch (luzActual) {
	case 0:
		light_color[0] = 1.f; light_color[1] = 1.f; light_color[2] = 0.f;
		break;
	case 1:
		light_color[0] = 1.f; light_color[1] = 0.f; light_color[2] = 1.f;
		break;
	case 2:
		light_color[0] = 0.f; light_color[1] = 1.f; light_color[2] = 1.f;
		break;
	case 3:
		light_color[0] = 1.f; light_color[1] = 1.f; light_color[2] = 1.f;
		break;
	}
}
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
GLfloat ControladorLuz::light_offset_y = 10.f;
GLfloat ControladorLuz::light_offset_z = 0.f;

stack<GLenum> ControladorLuz::lucesDisponibles;
stack<luz> ControladorLuz::lucesAMostrar;

void ControladorLuz::cargarLuces() {
	lucesDisponibles.push(GL_LIGHT1);
	lucesDisponibles.push(GL_LIGHT2);
	lucesDisponibles.push(GL_LIGHT3);
	lucesDisponibles.push(GL_LIGHT4);
	lucesDisponibles.push(GL_LIGHT5);
	lucesDisponibles.push(GL_LIGHT6);
	lucesDisponibles.push(GL_LIGHT7);
}

void ControladorLuz::pedirLuz(vector_3 pos, GLfloat color[4]) {
	if (!lucesDisponibles.empty()) {
		GLenum idLuzDisponible = lucesDisponibles.top();
		lucesDisponibles.pop();
		lucesAMostrar.push({
			idLuzDisponible,
			pos,
			{color[0], color[1], color[2], color[4]}
			}
		);
	}
}

void ControladorLuz::colocarLuces() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 
	light_position[0] = light_offset_x;
	light_position[1] = light_offset_y;
	light_position[2] = light_offset_z;
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);


	while (!lucesAMostrar.empty()) {
		luz luzAMostrar = lucesAMostrar.top();
		lucesAMostrar.pop();
		glEnable(luzAMostrar.idLuz);
		light_position[0] = luzAMostrar.posicion.x;
		light_position[1] = luzAMostrar.posicion.y;
		light_position[2] = luzAMostrar.posicion.z;
		glLightf(luzAMostrar.idLuz, GL_QUADRATIC_ATTENUATION, 0.05f); 
		glLightfv(luzAMostrar.idLuz, GL_POSITION, light_position);
		glLightfv(luzAMostrar.idLuz, GL_AMBIENT, luzAMostrar.color);
	}
}

void ControladorLuz::quitarLuces() {
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);
	glDisable(GL_LIGHT7);
	glDisable(GL_LIGHTING);

	while (!lucesDisponibles.empty())
		lucesDisponibles.pop();

	lucesDisponibles.push(GL_LIGHT1);
	lucesDisponibles.push(GL_LIGHT2);
	lucesDisponibles.push(GL_LIGHT3);
	lucesDisponibles.push(GL_LIGHT4);
	lucesDisponibles.push(GL_LIGHT5);
	lucesDisponibles.push(GL_LIGHT6);
	lucesDisponibles.push(GL_LIGHT7);
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
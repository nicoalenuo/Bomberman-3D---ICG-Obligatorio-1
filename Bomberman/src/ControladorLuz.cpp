#include "../lib/ControladorLuz.h"
#include "../lib/bomberman.h"

int ControladorLuz::colorLuzAmbiente = 0;
int ControladorLuz::colorLuzBonificador = 0;
GLfloat ControladorLuz::light_position[4] = { 0, 0, 0, 1 };
GLfloat ControladorLuz::light_color[4] = { 1, 1, 1, 1 };
GLfloat ControladorLuz::material_ambient_diffuse_color[4] = { 1, 1, 1, 1 };
GLfloat ControladorLuz::material_specular_color[4] = { 0, 0, 0, 1 };
GLfloat ControladorLuz::light_offset_x = 0.f;
GLfloat ControladorLuz::light_offset_y = 20.f;
GLfloat ControladorLuz::light_offset_z = 0.f;

void ControladorLuz::colocarLuces() {
	if (texturas_habilitadas) {
		glEnable(GL_LIGHTING);
		// Enable lighting (always after gluLookAt)
		glEnable(GL_LIGHT0); // enable light 0
		light_position[0] = (GLfloat)(jugador->getPosicion().x + light_offset_x);
		light_position[1] = (GLfloat)(jugador->getPosicion().y + light_offset_y);
		light_position[2] = (GLfloat)(jugador->getPosicion().z + light_offset_z);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
	}
}

void ControladorLuz::cambiarColorLuzAmbiente() {
	colorLuzAmbiente = (colorLuzAmbiente + 1) % 3;
	switch (colorLuzAmbiente) {
		case 0:
			light_color[0] = 0.8f; light_color[1] = 0.8f; light_color[2] = 0.2f;
			break;
		case 1:
			light_color[0] = 0.8f; light_color[1] = 0.4f; light_color[2] = 0.2f;
			break;
		case 2:
			light_color[0] = 0.f; light_color[1] = 0.2f; light_color[2] = 0.5f;
			break;
	}
}

void ControladorLuz::cambiarColorLuzBonificador() {
	colorLuzBonificador = (colorLuzBonificador + 1) % 3;
	switch (colorLuzBonificador) {
	case 0:
		light_color[0] = 1.f; light_color[1] = 1.f; light_color[2] = 0.f;
		break;
	case 1:
		light_color[0] = 1.f; light_color[1] = 0.f; light_color[2] = 1.f;
		break;
	case 2:
		light_color[0] = 0.f; light_color[1] = 1.f; light_color[2] = 1.f;
		break;
	}
}
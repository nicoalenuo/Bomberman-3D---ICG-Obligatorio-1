#include "../lib/ControladorLuz.h"

ControladorLuz* ControladorLuz::instancia = nullptr;

ControladorLuz* ControladorLuz::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorLuz();
	return instancia;
}

ControladorLuz::ControladorLuz() {
	colorLuzAmbiente = NOCHE;

	light_position[0] = 0;
	light_position[1] = 0;
	light_position[2] = 0;
	light_position[3] = 1;

	light_color[0] = 1;
	light_color[1] = 1;
	light_color[2] = 1;
	light_color[3] = 1;

	material_ambient_diffuse_color[0] = 0.5f;
	material_ambient_diffuse_color[1] = 0.5f;
	material_ambient_diffuse_color[2] = 0.5f;
	material_ambient_diffuse_color[3] = 0.0f;

	material_specular_color[0] = 0;
	material_specular_color[1] = 0;
	material_specular_color[2] = 0;
	material_specular_color[3] = 1;

	light_offset_x = 0.f;
	light_offset_y = 10.f;
	light_offset_z = -1.f;

	for (int idLuz = GL_LIGHT1; idLuz <= GL_LIGHT7; idLuz++) {
		lucesDisponibles.push(idLuz);
	}
}

void ControladorLuz::pedirLuz(vector_3 pos, GLfloat color[4]) {
	if (!lucesDisponibles.empty()) {
		lucesAMostrar.push({
			lucesDisponibles.top(),
			pos,
			{color[0], color[1], color[2], color[3]}
			}
		);
		lucesDisponibles.pop();
	}
}

void ControladorLuz::colocarLuces(vector_3 pos) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 
	light_position[0] = pos.x + light_offset_x;
	light_position[1] = pos.y + light_offset_y;
	light_position[2] = pos.z + light_offset_z;
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_ambient_diffuse_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular_color);

	while (!lucesAMostrar.empty()) {
		luz luzAMostrar = lucesAMostrar.top();
		lucesAMostrar.pop();
		glEnable(luzAMostrar.idLuz);
		light_position[0] = luzAMostrar.posicion.x;
		light_position[1] = luzAMostrar.posicion.y;
		light_position[2] = luzAMostrar.posicion.z;
		glLightf(luzAMostrar.idLuz, GL_QUADRATIC_ATTENUATION, 0.01f); //para que se concentre cerca del foco
		glLightfv(luzAMostrar.idLuz, GL_POSITION, light_position);
		glLightfv(luzAMostrar.idLuz, GL_AMBIENT, luzAMostrar.color);
	}
}

void ControladorLuz::quitarLuces() { 
	for (int idLuz = lucesDisponibles.empty() ? GL_LIGHT1 : lucesDisponibles.top() + 1; idLuz <= GL_LIGHT7; idLuz++) {
		lucesDisponibles.push(idLuz);
		glDisable(idLuz);
	}
	glDisable(GL_LIGHTING);
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

void ControladorLuz::moverCamara(vector_3 pos) {
	light_offset_x += pos.x;
	light_offset_y += pos.y;
	light_offset_z += pos.z;
}

ControladorLuz::~ControladorLuz() {

}
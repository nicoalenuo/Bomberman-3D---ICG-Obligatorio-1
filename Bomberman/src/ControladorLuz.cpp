#include "../lib/ControladorLuz.h"

ControladorLuz* ControladorLuz::instancia = nullptr;

ControladorLuz* ControladorLuz::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorLuz();
	return instancia;
}

ControladorLuz::ControladorLuz() {
	shininess = new GLfloat(128);

	colorLuzAmbiente = NOCHE;

	posicionLuz[0] = 0;
	posicionLuz[1] = 0;
	posicionLuz[2] = 0;
	posicionLuz[3] = 1;

	colorLuz[0] = 0.f; colorLuz[1] = 0.2f; colorLuz[2] = 0.5f;

	colorDiffuse[0] = 0.5f;
	colorDiffuse[1] = 0.5f;
	colorDiffuse[2] = 0.5f;
	colorDiffuse[3] = 0.5f;

	colorSpecular[0] = 1.0f;
	colorSpecular[1] = 1.0f;
	colorSpecular[2] = 1.0f;
	colorSpecular[3] = 1.0f;

	desplazamiento_luz = { 0.0f, 10.0f, -1.0f };

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
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, colorSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 
	posicionLuz[0] = pos.x + desplazamiento_luz.x;
	posicionLuz[1] = pos.y + desplazamiento_luz.y;
	posicionLuz[2] = pos.z + desplazamiento_luz.z;
	colorSpecular[0] = 0.1f;
	colorSpecular[1] = 0.1f;
	colorSpecular[2] = 0.1f;
	colorSpecular[3] = 0.1f;

	glLightfv(GL_LIGHT0, GL_AMBIENT, colorLuz);
	glLightfv(GL_LIGHT0, GL_SPECULAR, colorSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);


	colorSpecular[0] = 1.0f;
	colorSpecular[1] = 1.0f;
	colorSpecular[2] = 1.0f;
	colorSpecular[3] = 1.0f;

	while (!lucesAMostrar.empty()) {
		luz luzAMostrar = lucesAMostrar.top();
		lucesAMostrar.pop();
		glEnable(luzAMostrar.idLuz);
		posicionLuz[0] = luzAMostrar.posicion.x;
		posicionLuz[1] = luzAMostrar.posicion.y;
		posicionLuz[2] = luzAMostrar.posicion.z;
		glLightf(luzAMostrar.idLuz, GL_QUADRATIC_ATTENUATION, 0.01f); //para que se concentre cerca del foco
		glLightfv(luzAMostrar.idLuz, GL_AMBIENT, luzAMostrar.color);
		glLightfv(luzAMostrar.idLuz, GL_SPECULAR, colorSpecular);
		glLightfv(luzAMostrar.idLuz, GL_POSITION, posicionLuz);
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
	int luzActual = int(colorLuzAmbiente);
	luzActual = (luzActual + 1) % 4;
	colorLuzAmbiente = TIPO_LUZ_AMBIENTE(luzActual);
	switch (colorLuzAmbiente) {
		case MANIANA:
			colorLuz[0] = 0.8f; colorLuz[1] = 0.8f; colorLuz[2] = 0.2f;
			break;
		case TARDE:
			colorLuz[0] = 0.8f; colorLuz[1] = 0.4f; colorLuz[2] = 0.2f;
			break;
		case NOCHE:
			colorLuz[0] = 0.f; colorLuz[1] = 0.2f; colorLuz[2] = 0.5f;
			break;
		case SIN_LUZ_AMBIENTE:
			colorLuz[0] = 1.f; colorLuz[1] = 1.f; colorLuz[2] = 1.f;
			break;
	}
}

void ControladorLuz::moverLuzAmbiente(vector_3 pos) {
	desplazamiento_luz.x += pos.x;
	desplazamiento_luz.y += pos.y;
	desplazamiento_luz.z += pos.z;
}

ControladorLuz::~ControladorLuz() {

}
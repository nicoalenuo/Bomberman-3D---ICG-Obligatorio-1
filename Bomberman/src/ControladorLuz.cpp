#include "../lib/ControladorLuz.h"
#include "../lib/bomberman.h"

// DEJEN COMENTADO ESTO PQ ME OLVIDO LOS ENUMS Y NO QUIERO IR AL .h A CADA RATO
// enum TIPO_LUZ_AMBIENTE { MANIANA, TARDE, NOCHE, SIN_LUZ };

TIPO_LUZ_AMBIENTE ControladorLuz::colorLuzAmbiente = MANIANA;
GLfloat ControladorLuz::light_position[4] = { 0, 0, 0, 1 };
GLfloat ControladorLuz::light_color[4] = { 1, 1, 1, 1 };
GLfloat ControladorLuz::material_ambient_diffuse_color[4] = { 0.5f, 0.5f, 0.5f, 0.0f };
GLfloat ControladorLuz::material_specular_color[4] = { 0, 0, 0, 1 };
GLfloat ControladorLuz::light_offset_x = 0.f;
GLfloat ControladorLuz::light_offset_y = 10.f;
GLfloat ControladorLuz::light_offset_z = -1.f;

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
			{color[0], color[1], color[2], color[3]}
			}
		);
	}
}

void ControladorLuz::colocarLuces() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 
	//cout << "offset" << endl;
	//cout << "x:" << light_offset_x << " y:" << light_offset_y << " z:" << light_offset_z << endl;
	light_position[0] = jugador->getPosicion().x + light_offset_x;
	light_position[1] = jugador->getPosicion().y + light_offset_y;
	light_position[2] = jugador->getPosicion().z + light_offset_z;
	//cout << "posicion luz" << endl;
	//cout << "x: " << light_position[0] << " y:" << light_position[1] << " z:" << light_position[2] << endl;
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
		glLightf(luzAMostrar.idLuz, GL_QUADRATIC_ATTENUATION, 0.03f); //para que se concentre cerca del foco
		glLightfv(luzAMostrar.idLuz, GL_POSITION, light_position);
		glLightfv(luzAMostrar.idLuz, GL_AMBIENT, luzAMostrar.color);
	}
}

void ControladorLuz::quitarLuces() { //hay que rehacer esta función, no se está sacando las luces del arreglo de lucesAMostrar y no se lo está poniendo a lucesDisponibles
	if (!lucesDisponibles.empty()) {
		for (int idLuz = lucesDisponibles.top() + 1; idLuz <= GL_LIGHT7; idLuz++) {
			lucesDisponibles.push(idLuz);
			glDisable(idLuz);
		}
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
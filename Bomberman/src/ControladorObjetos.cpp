#include "../lib/ControladorObjetos.h"

ControladorObjetos* ControladorObjetos::instancia = nullptr;

ControladorObjetos* ControladorObjetos::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorObjetos();
	return instancia;
}

ControladorObjetos::ControladorObjetos() {
	ControladorObjetos::cargarObj("objs/player.obj", player_commands, player_data);
	ControladorObjetos::cargarObj("objs/bomba.obj", bomba_commands, bomba_data);
	ControladorObjetos::cargarObj("objs/enemy.obj", enemy_commands, enemy_data);
}

void ControladorObjetos::cargarObj(string file, vector<char>& commands_output, vector<vector<float>>& data_output) {
	ifstream file_stream(file);
	if (!file_stream) {
		cerr << "Cannot open: " << file << endl;
		exit(1);
	}
	vector<char> commands;
	vector<vector<float>> data;

	vector<unsigned int> vertex_indices, uv_indices, normal_indices;
	vector<vector<float>> temp_vertices, temp_uvs, temp_normals;

	string line, subline, command, face1, face2, face3, face4;
	vector<string> faces;
	float x, y, z;
	unsigned int aux;


	while (getline(file_stream, line)) {

		file_stream >> command;

		if (command == "v") {
			file_stream >> x >> y >> z;
			temp_vertices.push_back({ x, y, z });
		}
		else if (command == "vt") {
			file_stream >> x >> y;
			temp_uvs.push_back({ x, y });
		}
		else if (command == "vn") {
			file_stream >> x >> y >> z;
			temp_normals.push_back({ x, y, z });
		}
		else if (command == "f") {
			file_stream >> face1 >> face2 >> face3;
			faces = { face1, face2, face3 };
			for (size_t i = 0; i < faces.size(); i++) {
				istringstream sub_stream(faces[i]);
				getline(sub_stream, subline, '/');
				if (stoi(subline) < 0) {
					aux = temp_vertices.size() - stoi(subline);
				}
				else {
					aux = stoi(subline) - 1;
				}
				vertex_indices.push_back(aux);

				getline(sub_stream, subline, '/');
				if (stoi(subline) < 0) {
					aux = temp_uvs.size() - stoi(subline);
				}
				else {
					aux = stoi(subline) - 1;
				}
				uv_indices.push_back(aux);

				getline(sub_stream, subline, '/');
				if (stoi(subline) < 0) {
					aux = temp_normals.size() - stoi(subline);
				}
				else {
					aux = stoi(subline) - 1;
				}
				normal_indices.push_back(aux);
			}
		}
	}
	commands.push_back('C');
	data.push_back({ 1.f, 1.f, 1.f });
	for (size_t i = 0; i < uv_indices.size(); i++) {
		commands.push_back('T'); data.push_back(temp_uvs[uv_indices[i]]);
		commands.push_back('N'); data.push_back(temp_normals[normal_indices[i]]);
		commands.push_back('V'); data.push_back(temp_vertices[vertex_indices[i]]);
	}

	commands_output = commands;
	data_output = data;
}

vector<char> commands;
vector<vector<float>> data_obj;
GLuint texture;
void ControladorObjetos::dibujar(tipo_obj obj) {
	switch (obj) {
		case (OBJ_PLAYER):
			commands = player_commands;
			data_obj = player_data;
			texture = ControladorTexturas::getInstance()->getTextura(PLAYER);
			break;
		case (OBJ_BOMBA):
			commands = bomba_commands;
			data_obj = bomba_data;
			texture = ControladorTexturas::getInstance()->getTextura(TEXTURA_BOMBA);
			break;
		case (OBJ_ENEMY_ROJO):
			commands = enemy_commands;
			data_obj = enemy_data;
			if (texturas_habilitadas) {
				texture = ControladorTexturas::getInstance()->getTextura(TEXTURA_ENEMY_ROJO);
			}
			break;
		case (OBJ_ENEMY_AZUL):
			commands = enemy_commands;
			data_obj = enemy_data;
			if (texturas_habilitadas) {
				texture = ControladorTexturas::getInstance()->getTextura(TEXTURA_ENEMY_AZUL);
			}
			break;
		case (OBJ_ENEMY_VERDE):
			commands = enemy_commands;
			data_obj = enemy_data;
			if (texturas_habilitadas) {
				texture = ControladorTexturas::getInstance()->getTextura(TEXTURA_ENEMY_VERDE);
			}
			break;
	}

	if (texturas_habilitadas) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	glBegin(GL_TRIANGLES);

	for (size_t i = 0; i < commands.size(); i++) {
		switch (commands[i]) {
			case('V'): {
				glVertex3f(data_obj[i][0], data_obj[i][1], data_obj[i][2]);
				break;
			}
			case('T'): {
				glTexCoord2d(data_obj[i][0], data_obj[i][1]);
				break;
			}
			case('N'): {
				glNormal3f(data_obj[i][0], data_obj[i][1], data_obj[i][2]);
				break;
			}
			case('C'): {
				glColor3f(data_obj[i][0], data_obj[i][1], data_obj[i][2]);
				break;
			}
			case('A'): {
				glColor4f(data_obj[i][0], data_obj[i][1], data_obj[i][2], data_obj[i][3]);
				break;
			}
		}
	}
	glEnd();

	if (texturas_habilitadas) {
		glDisable(GL_TEXTURE_2D);
	}
}

void ControladorObjetos::dibujarCubo(vector_3 tam, GLuint textura, GLfloat color[3]) {
	if (texturas_habilitadas && textura != 0) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textura);
		glColor3f(1.0f, 1.0f, 1.0f);
	} else if (color != nullptr){
		glColor3f(color[0], color[1], color[2]);
	}

	glBegin(GL_QUADS);

	// Cara de abajo
	glNormal3f(0.0f, -1.0f, 0.0f); // Normal hacia abajo

	glTexCoord2f(0, 0);
	glVertex3f(-tam.x, 0, -tam.z);

	glTexCoord2f(0, 1);
	glVertex3f(tam.x, 0, -tam.z);

	glTexCoord2f(1, 1);
	glVertex3f(tam.x, 0, tam.z);

	glTexCoord2f(1, 0);
	glVertex3f(-tam.x, 0, tam.z);

	// Cara de arriba
	glNormal3f(0.0f, 1.0f, 0.0f); // Normal hacia arriba

	glTexCoord2f(0, 0);
	glVertex3f(-tam.x, tam.y, -tam.z);

	glTexCoord2f(0, 1);
	glVertex3f(tam.x, tam.y, -tam.z);

	glTexCoord2f(1, 1);
	glVertex3f(tam.x, tam.y, tam.z);

	glTexCoord2f(1, 0);
	glVertex3f(-tam.x, tam.y, tam.z);

	// Cara de atras
	glNormal3f(0.0f, 0.0f, -1.0f); // Normal hacia atr�s

	glTexCoord2f(0, 0);
	glVertex3f(-tam.x, 0, -tam.z);

	glTexCoord2f(1, 0);
	glVertex3f(tam.x, 0, -tam.z);

	glTexCoord2f(1, 1);
	glVertex3f(tam.x, tam.y, -tam.z);

	glTexCoord2f(0, 1);
	glVertex3f(-tam.x, tam.y, -tam.z);



	// Cara de adelante
	glNormal3f(0.0f, 0.0f, 1.0f); // Normal hacia adelante

	glTexCoord2f(0, 0);
	glVertex3f(-tam.x, 0, tam.z);

	glTexCoord2f(0, 1);
	glVertex3f(-tam.x, tam.y, tam.z);

	glTexCoord2f(1, 1);
	glVertex3f(tam.x, tam.y, tam.z);

	glTexCoord2f(1, 0);
	glVertex3f(tam.x, 0, tam.z);

	// Cara izquierda
	glNormal3f(-1.0f, 0.0f, 0.0f); // Normal hacia la izquierda

	glTexCoord2f(0, 0);
	glVertex3f(-tam.x, 0, -tam.z);

	glTexCoord2f(0, 1);
	glVertex3f(-tam.x, tam.y, -tam.z);

	glTexCoord2f(1, 1);
	glVertex3f(-tam.x, tam.y, tam.z);

	glTexCoord2f(1, 0);
	glVertex3f(-tam.x, 0, tam.z);

	// Cara derecha
	glNormal3f(1.0f, 0.0f, 0.0f); // Normal hacia la derecha

	glTexCoord2f(0, 0);
	glVertex3f(tam.x, 0, tam.z);

	glTexCoord2f(0, 1);
	glVertex3f(tam.x, tam.y, tam.z);

	glTexCoord2f(1, 1);
	glVertex3f(tam.x, tam.y, -tam.z);

	glTexCoord2f(1, 0);
	glVertex3f(tam.x, 0, -tam.z);

	glEnd();

	if (texturas_habilitadas && textura != 0) {
		glDisable(GL_TEXTURE_2D);
	}
}

void ControladorObjetos::dibujarSuelo() {

	glColor3f(0.75f, 0.63f, 0.50f);

	if (texturas_habilitadas) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ControladorTexturas::getInstance()->getTextura(TEXTURA_SUELO));
		glColor3f(1.0f, 1.0f, 1.0f);
	}

	glBegin(GL_QUADS);

	glNormal3f(0.0f, 1.0f, 0.0f);

	glTexCoord2d(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2d(largoTablero, 0);
	glVertex3f(largoTablero * tile_size, 0, 0);

	glTexCoord2d(largoTablero , anchoTablero);
	glVertex3f(largoTablero * tile_size, 0, anchoTablero * tile_size);

	glTexCoord2d(0, anchoTablero );
	glVertex3f(0, 0, anchoTablero * tile_size);

	glEnd();

	if (texturas_habilitadas) {
		glDisable(GL_TEXTURE_2D);
	}

	glColor3f(0.0f, 1.0f, 0.0f);

	if (texturas_habilitadas) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ControladorTexturas::getInstance()->getTextura(TEXTURA_PASTO));
		glColor3f(1.0f, 1.0f, 1.0f);
	}

	glBegin(GL_QUADS);

	glNormal3f(0.0f, 1.0f, 0.0f);

	glTexCoord2d(-1000, -1000);
	glVertex3f(-1000.0f, -0.1f, -1000.0f);

	glTexCoord2d(1000, -1000);
	glVertex3f(1000.0f, -0.1f, -1000.0f);

	glTexCoord2d(1000, 1000);
	glVertex3f(1000.0f, -0.1f, 1000.0f);

	glTexCoord2d(-1000, 1000);
	glVertex3f(-1000, -0.1f, 1000);

	glEnd();

	if (texturas_habilitadas) {
		glDisable(GL_TEXTURE_2D);
	}
}

void ControladorObjetos::dibujarMarcadorBomba(vector_3 pos) {
	int posX, posZ;

	if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_MENOS_X)) {
		posX = getIndiceTablero(pos.x - tile_size);
		posZ = getIndiceTablero(pos.z);
	}
	else if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_Z)) {
		posX = getIndiceTablero(pos.x);
		posZ = getIndiceTablero(pos.z + tile_size);
	}
	else if (ControladorCamara::getInstance()->camaraMiraHacia(EJE_X)) {
		posX = getIndiceTablero(pos.x + tile_size);
		posZ = getIndiceTablero(pos.z);
	}
	else {
		posX = getIndiceTablero(pos.x);
		posZ = getIndiceTablero(pos.z - tile_size);
	}


	if (posX >= 0 && posX < largoTablero && posZ >= 0 && posZ < anchoTablero && estructuras[posX][posZ] == nullptr && bombas[posX][posZ] == nullptr) {

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor4f(0.7f, 0.0f, 0.0f, 0.3f);

		glBegin(GL_QUADS);

		glVertex3f(posX * tile_size + tile_size / 8, 0.02f, posZ * tile_size + tile_size / 8);
		glVertex3f(posX * tile_size + 7 * tile_size / 8, 0.02f, posZ * tile_size + tile_size / 8);
		glVertex3f(posX * tile_size + 7 * tile_size/8, 0.02f, posZ * tile_size + 7 * tile_size / 8);
		glVertex3f(posX * tile_size + tile_size / 8, 0.02f, posZ * tile_size + 7 * tile_size / 8);

		glEnd();
		glDisable(GL_BLEND);
	}
}

ControladorObjetos::~ControladorObjetos() {

}
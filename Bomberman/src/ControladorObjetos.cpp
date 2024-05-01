#include "../lib/ControladorObjetos.h"

vector<char> ControladorObjetos::bomba_commands;
vector<vector<float>> ControladorObjetos::bomba_data;
vector<char> ControladorObjetos::player_commands;
vector<vector<float>> ControladorObjetos::player_data;

void ControladorObjetos::cargarObjetos() {
	tie(player_commands, player_data) = ControladorObjetos::cargarObj("objs/player.obj", 0);
	tie(bomba_commands, bomba_data) = ControladorObjetos::cargarObj("objs/bomba.obj", 0);
}

tuple<vector<char>, vector<vector<float>>> ControladorObjetos::cargarObj(string file, int type) {
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
			if (type == 1) {
				file_stream >> face1 >> face2 >> face3 >> face4;
				faces = { face1, face2, face3, face4 };
			}
			else { // Triangulos
				file_stream >> face1 >> face2 >> face3;
				faces = { face1, face2, face3 };
			}
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

	return { commands, data };
}

GLenum primitive;
vector<char> commands;
vector<vector<float>> data_obj;
GLuint texture;
void ControladorObjetos::dibujar(tipo_obj obj) {
	switch (obj) {
		case (OBJ_PLAYER):
			primitive = GL_TRIANGLES;
			commands = player_commands;
			data_obj = player_data;
			texture = ControladorTexturas::getTextura(PLAYER);
			break;
		case (OBJ_BOMBA):
			primitive = GL_TRIANGLES;
			commands = bomba_commands;
			data_obj = bomba_data;
			texture = ControladorTexturas::getTextura(TEXTURA_BOMBA);
			break;
	}

	if (texturas_habilitadas) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	glBegin(primitive);
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

	if (texturas_habilitadas)
		glDisable(GL_TEXTURE_2D);
}

void ControladorObjetos::dibujarCubo(vector_3 tam, GLuint textura, GLfloat color[3]) {
	if (texturas_habilitadas && textura != 0) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textura);
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (textura == 0){
		glColor3f(color[0], color[1], color[2]);
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);
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

	// Cara de atrás
	glNormal3f(0.0f, 0.0f, -1.0f); // Normal hacia atrás

	glTexCoord2f(0, 0);
	glVertex3f(-tam.x, 0, -tam.z);

	glTexCoord2f(0, 1);
	glVertex3f(tam.x, 0, -tam.z);

	glTexCoord2f(1, 1);
	glVertex3f(tam.x, tam.y, -tam.z);

	glTexCoord2f(1, 0);
	glVertex3f(-tam.x, tam.y, -tam.z);

	// Cara de adelante
	glNormal3f(0.0f, 0.0f, 1.0f); // Normal hacia adelante

	glTexCoord2f(0, 0);
	glVertex3f(-tam.x, 0, tam.z);

	glTexCoord2f(0, 1);
	glVertex3f(tam.x, 0, tam.z);

	glTexCoord2f(1, 1);
	glVertex3f(tam.x, tam.y, tam.z);

	glTexCoord2f(1, 0);
	glVertex3f(-tam.x, tam.y, tam.z);

	// Cara izquierda
	glNormal3f(-1.0f, 0.0f, 0.0f); // Normal hacia la izquierda

	glTexCoord2f(0, 0);
	glVertex3f(-tam.x, 0, -tam.z);

	glTexCoord2f(0, 1);
	glVertex3f(-tam.x, 0, tam.z);

	glTexCoord2f(1, 1);
	glVertex3f(-tam.x, tam.y, tam.z);

	glTexCoord2f(1, 0);
	glVertex3f(-tam.x, tam.y, -tam.z);

	// Cara derecha
	glNormal3f(1.0f, 0.0f, 0.0f); // Normal hacia la derecha

	glTexCoord2f(0, 0);
	glVertex3f(tam.x, 0, -tam.z);

	glTexCoord2f(0, 1);
	glVertex3f(tam.x, 0, tam.z);

	glTexCoord2f(1, 1);
	glVertex3f(tam.x, tam.y, tam.z);

	glTexCoord2f(1, 0);
	glVertex3f(tam.x, tam.y, -tam.z);

	glEnd();

	if (texturas_habilitadas)
		glDisable(GL_TEXTURE_2D);
}
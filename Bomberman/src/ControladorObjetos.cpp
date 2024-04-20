#include "../lib/ControladorObjetos.h"

tuple<vector<char>, vector<vector<float>>> ControladorObjetos::load_obj(string file, int type) {
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
			else { // Conformed by triangles
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


void ControladorObjetos::DrawMultiplePoints(GLenum primitive, vector<char> commands, vector<vector<float>> data, GLuint texture) {
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1.f, 1.f, 1.f);

	glBegin(primitive);
	for (size_t i = 0; i < commands.size(); i++) {
		switch (commands[i]) {
			case('V'): {
				glVertex3f(data[i][0], data[i][1], data[i][2]);
				break;
			}
			case('T'): {
				glTexCoord2d(data[i][0], data[i][1]);
				break;
			}
			case('N'): {
				glNormal3f(data[i][0], data[i][1], data[i][2]);
				break;
			}
			case('C'): {
				glColor3f(data[i][0], data[i][1], data[i][2]);
				break;
			}
			case('A'): {
				glColor4f(data[i][0], data[i][1], data[i][2], data[i][3]);
				break;
			}
		}
	}
	glEnd();
}
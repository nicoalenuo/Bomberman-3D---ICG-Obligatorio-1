#include "../lib/ControladorObjetos.h"

ControladorObjetos* ControladorObjetos::instancia = nullptr;

ControladorObjetos* ControladorObjetos::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorObjetos();
	return instancia;
}

ControladorObjetos::ControladorObjetos() {
	ControladorObjetos::cargarObj("objs/player.obj", player_data);
	ControladorObjetos::cargarObj("objs/bomba.obj", bomba_data);
	ControladorObjetos::cargarObj("objs/enemy.obj", enemy_data);

	//Se generan display lists una unica vez, para ser llamadas repetidas veces luego

	displayListIds[OBJ_PLAYER] = glGenLists(1);
	glNewList(displayListIds[OBJ_PLAYER], GL_COMPILE);
	cargarDisplayList(OBJ_PLAYER);
	glEndList();

	displayListIds[OBJ_ENEMY_ROJO] = glGenLists(2);
	glNewList(displayListIds[OBJ_ENEMY_ROJO], GL_COMPILE);
	cargarDisplayList(OBJ_ENEMY_ROJO);
	glEndList();

	displayListIds[OBJ_ENEMY_VERDE] = glGenLists(3);
	glNewList(displayListIds[OBJ_ENEMY_VERDE], GL_COMPILE);
	cargarDisplayList(OBJ_ENEMY_VERDE);
	glEndList();

	displayListIds[OBJ_ENEMY_AZUL] = glGenLists(4);
	glNewList(displayListIds[OBJ_ENEMY_AZUL], GL_COMPILE);
	cargarDisplayList(OBJ_ENEMY_AZUL);
	glEndList();
}

void ControladorObjetos::cargarObj(string file, pair<vector<char>, vector<vector<float>>>& data_output) {
	ifstream file_stream(file);
	if (!file_stream) {
		cerr << "No se pudo abrir: " << file << endl;
		exit(1);
	}
	vector<char> comandos;
	vector<vector<float>> data;

	vector<int> vertex_indices, uv_indices, normal_indices;
	vector<vector<float>> temp_vertices, temp_uvs, temp_normals;

	string line, subline, comando, face1, face2, face3, face4;
	vector<string> faces;
	float x, y, z;
	unsigned int aux;


	while (getline(file_stream, line)) {

		file_stream >> comando;

		if (comando == "v") {
			file_stream >> x >> y >> z;
			temp_vertices.push_back({ x, y, z });
		}
		else if (comando == "vt") {
			file_stream >> x >> y;
			temp_uvs.push_back({ x, y });
		}
		else if (comando == "vn") {
			file_stream >> x >> y >> z;
			temp_normals.push_back({ x, y, z });
		}
		else if (comando == "f") {
			file_stream >> face1 >> face2 >> face3;
			faces = { face1, face2, face3 };
			for (size_t i = 0; i < 3; i++) {
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
	comandos.push_back('C');
	data.push_back({ 1.f, 1.f, 1.f });
	for (size_t i = 0; i < uv_indices.size(); i++) {
		comandos.push_back('T'); data.push_back(temp_uvs[uv_indices[i]]);
		comandos.push_back('N'); data.push_back(temp_normals[normal_indices[i]]);
		comandos.push_back('V'); data.push_back(temp_vertices[vertex_indices[i]]);
	}

	data_output = { comandos, data };
}

void ControladorObjetos::cargarDisplayList(tipo_obj obj) {
	pair<vector<char>, vector<vector<float>>> data_obj;
	GLuint textura = 0;
	switch (obj) {
	case OBJ_PLAYER:
		data_obj = player_data;
		textura = ControladorTexturas::getInstance()->getTextura(PLAYER);
		break;
	case OBJ_BOMBA:
		data_obj = bomba_data;
		textura = ControladorTexturas::getInstance()->getTextura(TEXTURA_BOMBA);
		break;
	case OBJ_ENEMY_ROJO:
	case OBJ_ENEMY_AZUL:
	case OBJ_ENEMY_VERDE:
		data_obj = enemy_data;
		if (texturas_habilitadas) {
			textura = ControladorTexturas::getInstance()->getTextura(
				(obj == OBJ_ENEMY_ROJO) ? TEXTURA_ENEMY_ROJO :
				(obj == OBJ_ENEMY_AZUL) ? TEXTURA_ENEMY_AZUL :
				TEXTURA_ENEMY_VERDE
			);
		}
		break;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);

	const vector<char>& comandos = data_obj.first;
	const vector<vector<float>>& data = data_obj.second;

	glBegin(GL_TRIANGLES);

	for (size_t i = 0; i < data.size(); ++i) {
		const char comando = comandos[i];
		const vector<float>& values = data[i];

		if (comando == 'V') {
			glVertex3f(values[0], values[1], values[2]);
		}
		else if (comando == 'T') {
			glTexCoord2f(values[0], values[1]);
		}
		else if (comando == 'N') {
			glNormal3f(values[0], values[1], values[2]);
		}
		else if (comando == 'C') {
			glColor3f(values[0], values[1], values[2]);
		}
		else if (comando == 'A') {
			glColor4f(values[0], values[1], values[2], values[3]);
		}
	}

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void ControladorObjetos::dibujar(tipo_obj obj, GLfloat transparencia) {
	if (texturas_habilitadas && displayListIds.count(obj) == 1) { //si tiene una display list, la utiliza
		glCallList(displayListIds[obj]);
		return;
	}

	pair<vector<char>, vector<vector<float>>> data_obj;
	GLuint textura;
	switch (obj) {
	case OBJ_PLAYER:
		data_obj = player_data;
		textura = ControladorTexturas::getInstance()->getTextura(PLAYER);
		break;
	case OBJ_BOMBA:
		data_obj = bomba_data;
		textura = ControladorTexturas::getInstance()->getTextura(TEXTURA_BOMBA);
		break;
	case OBJ_ENEMY_ROJO:
	case OBJ_ENEMY_AZUL:
	case OBJ_ENEMY_VERDE:
		data_obj = enemy_data;
		if (texturas_habilitadas) {
			textura = ControladorTexturas::getInstance()->getTextura(
				(obj == OBJ_ENEMY_ROJO) ? TEXTURA_ENEMY_ROJO :
				(obj == OBJ_ENEMY_AZUL) ? TEXTURA_ENEMY_AZUL :
				TEXTURA_ENEMY_VERDE
			);
		}
		break;
	default:
		textura = 0;
		return; 
	}

	if (texturas_habilitadas) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textura);
	}

	const vector<char>& comandos = data_obj.first;
	const vector<vector<float>>& data = data_obj.second;

	glBegin(GL_TRIANGLES);

	for (size_t i = 0; i < data.size(); ++i) {
		const char comando = comandos[i];
		const vector<float>& values = data[i];

		if (comando == 'V') {
			glVertex3f(values[0], values[1], values[2]);
		}
		else if (comando == 'T') {
			glTexCoord2f(values[0], values[1]);
		}
		else if (comando == 'N') {
			glNormal3f(values[0], values[1], values[2]);
		}
		else if (comando == 'C') {
			glColor4f(values[0], values[1], values[2], transparencia);
		}
		else if (comando == 'A') {
			glColor4f(values[0], values[1], values[2], values[3]);
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

		if (!wireframe) {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(posX * tile_size + tile_size / 2, 0.0f, posZ * tile_size + tile_size / 2);
		dibujar(OBJ_BOMBA, 0.8f);
		glDisable(GL_BLEND);
		if (!wireframe){
			glDisable(GL_CULL_FACE);
		}
	}
}

ControladorObjetos::~ControladorObjetos() {

}
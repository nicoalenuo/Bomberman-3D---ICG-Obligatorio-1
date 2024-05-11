#pragma once

#ifndef CONTROLADOROBJETOS_H
#define CONTROLADOROBJETOS_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "SDL_opengl.h"

#include "global.h"
#include "ControladorTexturas.h"
#include "ControladorCamara.h"

using namespace std;

enum tipo_obj {
    OBJ_PLAYER,
    OBJ_BOMBA,
    OBJ_ENEMY_ROJO,
    OBJ_ENEMY_AZUL,
    OBJ_ENEMY_VERDE
};

class ControladorObjetos{
private:
    static ControladorObjetos* instancia;
    ControladorObjetos();

    pair<vector<char>, vector<vector<float>>> bomba_data;
    pair<vector<char>, vector<vector<float>>> player_data;
    pair<vector<char>, vector<vector<float>>> enemy_data;

    void cargarObj(string file, pair<vector<char>, vector<vector<float>>>&data_output);
public:
    static ControladorObjetos* getInstance();

    void dibujar(tipo_obj obj, GLfloat transparencia);
    void dibujarCubo(vector_3 tam, GLuint textura, GLfloat color[3]); //textura es 0 si no tiene
    void dibujarSuelo();
    void dibujarMarcadorBomba(vector_3 pos);

    ~ControladorObjetos();
};

#endif


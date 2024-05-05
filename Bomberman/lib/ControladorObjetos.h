#pragma once

#ifndef CONTROLADOROBJETOS_H
#define CONTROLADOROBJETOS_H

#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>

#include "SDL_opengl.h"

#include "global.h"
#include "ControladorTexturas.h"
#include "ControladorCamara.h"

using namespace std;

enum tipo_obj {
    OBJ_PLAYER,
    OBJ_BOMBA
};

class ControladorObjetos{
private:
    static vector<char>  bomba_commands;
    static vector<vector<float>> bomba_data;

    static vector<char>  player_commands;
    static vector<vector<float>> player_data;

    static void cargarObj(string file, vector<char> &commands_output, vector<vector<float>> &data_output);
public:
    static void cargarObjetos();
    static void dibujar(tipo_obj obj);
    static void dibujarCubo(vector_3 tam, GLuint textura, GLfloat color[3]); //textura es 0 si no tiene
    static void dibujarSuelo();
    static void dibujarMarcadorBomba(vector_3 pos);
};

#endif


#pragma once

#ifndef CONTROLADOROBJETOS_H
#define CONTROLADOROBJETOS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>

#include "SDL_opengl.h"

#include "global.h"
#include "ControladorTexturas.h"

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

    static tuple<vector<char>, vector<vector<float>>> cargarObj(string file, int type);
public:
    static void cargarObjetos();
    static void dibujar(tipo_obj obj);
    static void dibujarCubo(vector_3 tam, GLuint textura, GLfloat color[3]); //textura es 0 si no tiene
    static void dibujarSuelo();
};

#endif


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

using namespace std;

class ControladorObjetos{
public:
    static tuple<vector<char>, vector<vector<float>>> cargarObj(string file, int type);
    static void dibujar(GLenum primitive, vector<char> commands, vector<vector<float>> data, GLuint texture);
};

#endif


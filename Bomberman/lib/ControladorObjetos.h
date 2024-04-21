#pragma once

#ifndef CONTROLADOROBJETOS_H
#define CONTROLADOROBJETOS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>

#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>

using namespace std;

class ControladorObjetos{
public:
    static tuple<vector<char>, vector<vector<float>>> load_obj(string file, int type);
    static void DrawMultiplePoints(GLenum primitive, vector<char> commands, vector<vector<float>> data, GLuint texture);
};

#endif


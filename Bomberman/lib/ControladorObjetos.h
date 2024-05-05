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
    static vector<char>  bomba_commands;
    static vector<vector<float>> bomba_data;

    static vector<char>  player_commands;
    static vector<vector<float>> player_data;

    
    static vector<char>  enemy_commands;
    static vector<vector<float>> enemy_data;

    static void cargarObj(string file, vector<char> &commands_output, vector<vector<float>> &data_output);
public:
    static void cargarObjetos();
    static void dibujar(tipo_obj obj);
    static void dibujarCubo(vector_3 tam, GLuint textura, GLfloat color[3]); //textura es 0 si no tiene
    static void dibujarSuelo();
    static void dibujarMarcadorBomba(vector_3 pos);
};

#endif


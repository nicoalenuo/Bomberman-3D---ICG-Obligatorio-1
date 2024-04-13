#pragma once

using namespace std;

#include "bomba.h"
#include <list>

class global { //abstracta
private:
	//no debe tener nada
public:
	//aqui van funciones que sean utilizadas por varias clases pero que no dependan del controlador
	// TODA FUNCION DEBE IR CON STATIC
	static void insertarBomba(list<bomba*> listBomb, bomba* bomb);
};
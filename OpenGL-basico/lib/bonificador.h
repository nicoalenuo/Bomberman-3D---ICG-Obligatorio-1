#pragma once
#include <string>

using namespace std;

#include "objeto.h"

class bonificador : public objeto {
private:
	string nombre; //tipo de poder
public:
	bonificador(int x, int z);
	virtual string getNombre();
	virtual void setNombre(string nom);
};


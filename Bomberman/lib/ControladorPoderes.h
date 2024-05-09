#pragma once

#ifndef CONTROLADOR_PODERES_H
#define CONTROLADOR_PODERES_H

#include <map>
#include <iostream>
#include "global.h"

using namespace std;

enum tipo_poder { //agregar aca en caso de agregar mas bonificadores, y luego agregar casos al switch ControladorInterfaz
	AUMENTAR_CANTIDAD_BOMBAS,
	AUMENTAR_ALCANCE_BOMBAS,
	INMORTALIDAD, // segundos de inmortalidad
	AUMENTAR_VELOCIDAD, //
	BOMBAS_ATRAVIESAN_ESTRUCTURAS,
	BONIFICADOR_RANDOM, //NO ELIMINAR ESTE
};

class ControladorPoderes {
private: //Los poderes con temporizador tienen un tiempo. Los que no, no se pierden y duran hasta el siguiente nivel/fin de juego
	static ControladorPoderes* instancia;
	ControladorPoderes();

	map<tipo_poder, int> poderActivo;
	map<tipo_poder, int> temporizadorPoder;
public:
	static ControladorPoderes* getInstance();

	void resetearPoderes();
	void actualizarTemporizadores();
	int getValor(tipo_poder poder);
	bool poderDependeDeTiempo(tipo_poder poder);
	bool poderEsBooleano(tipo_poder poder);
	void activarPoder(tipo_poder poder, int temporizador);
	void desactivarPoder(tipo_poder poder);
	map<tipo_poder, int> obtenerPoderes();

	~ControladorPoderes();
};

#endif
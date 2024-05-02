#pragma once

#ifndef CONTROLADOR_PODERES_H
#define CONTROLADOR_PODERES_H

#include <list>
#include <iostream>
#include "global.h"

using namespace std;

enum tipo_poder { //agregar aca en caso de agregar mas bonificadores, y luego agregar casos al switch ControladorInterfaz
	AUMENTAR_ALCANCE_BOMBAS,
	INMORTALIDAD, // segundos de inmortalidad
	AUMENTAR_VELOCIDAD, // solo del jugador
	BOMBAS_ATRAVIESAN_ESTRUCTURAS, // booleano
	AUMENTAR_CANTIDAD_BOMBAS,
	BONIFICADOR_RANDOM, //NO ELIMINAR ESTE
	//MOVER_BOMBA //este aún no lo vamos a meter
};

struct poder {
	tipo_poder tipoPoder;
	float valorPoder;
};

class ControladorPoderes{
private: //Los poderes con temporizador tienen un tiempo. Los que no, no se pierden y duran hasta el siguiente nivel/fin de juego
	static list<poder*> poderes; //realmente no son temporizadores, son valores de los poderes, algunos son tiempos, otros no
public:
	static void cargarPoderes();
	static bool poderDependeTiempo(tipo_poder poder);
	static bool poderEsBooleano(tipo_poder poder);
	static void actualizarPoderes();
	static float getValor(tipo_poder poder);
	static void agregarPoder(tipo_poder poder);
	static bool getEstaActivo(tipo_poder poder);
};

#endif
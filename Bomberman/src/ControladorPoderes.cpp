#include "../lib/ControladorPoderes.h"

map<tipo_poder, int> ControladorPoderes::poderActivo;
map<tipo_poder, int> ControladorPoderes::temporizadorPoder;

void ControladorPoderes::cargarPoderes() {
	temporizadorPoder[INMORTALIDAD] = 0;
	temporizadorPoder[AUMENTAR_VELOCIDAD] = 0;
	poderActivo[BOMBAS_ATRAVIESAN_ESTRUCTURAS] = 0;
	poderActivo[AUMENTAR_CANTIDAD_BOMBAS] = 0;
	poderActivo[AUMENTAR_ALCANCE_BOMBAS] = 0;
}

void ControladorPoderes::actualizarTemporizadores() {
	for (pair<const tipo_poder, int>& kv : temporizadorPoder) {
		if (kv.second > 0)
			kv.second -= int(elapsed_time);
		if (kv.second <= 0)
			kv.second = 0;
	}
}

int ControladorPoderes::getValor(tipo_poder poder) {
	return temporizadorPoder.count(poder) == 1 ? 
		temporizadorPoder[poder] :
		poderActivo[poder];
}

bool ControladorPoderes::poderDependeDeTiempo(tipo_poder poder) {
	return temporizadorPoder.count(poder) == 1;
}

bool ControladorPoderes::poderEsBooleano(tipo_poder poder) {
	return poder == BOMBAS_ATRAVIESAN_ESTRUCTURAS;
}

map<tipo_poder, int> ControladorPoderes::obtenerPoderes() {
	map<tipo_poder, int> poderes = map<tipo_poder, int>();
	for (auto it = temporizadorPoder.begin(); it != temporizadorPoder.end(); ++it) {
		poderes.insert(*it);
	}
	for (auto it = poderActivo.begin(); it != poderActivo.end(); ++it) {
		poderes.insert(*it);
	}
	return poderes;
}

void ControladorPoderes::activarPoder(tipo_poder poder, int valor) {
	if (temporizadorPoder.count(poder) == 1)
		temporizadorPoder[poder] += valor;
	else
		poderActivo[poder] += valor;
}

void ControladorPoderes::desactivarPoder(tipo_poder poder) {
	if (temporizadorPoder.count(poder) == 1) 
		temporizadorPoder[poder] = 0;
	else 
		poderActivo[poder] = 0;
}
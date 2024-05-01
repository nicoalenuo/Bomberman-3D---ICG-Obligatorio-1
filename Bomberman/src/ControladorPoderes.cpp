#include "../lib/ControladorPoderes.h"

map<tipo_poder, bool> ControladorPoderes::poderActivo;
map<tipo_poder, int> ControladorPoderes::temporizadorPoder;

void ControladorPoderes::cargarPoderes() {
	temporizadorPoder[INMORTALIDAD] = 0; 
	temporizadorPoder[BOMBAS_ATRAVIESAN_ESTRUCTURAS] = 0; 
	poderActivo[AUMENTAR_VELOCIDAD] = false;
	poderActivo[AUMENTAR_CANTIDAD_BOMBAS] = false;
	poderActivo[AUMENTAR_ALCANCE_BOMBAS] = false;
}

void ControladorPoderes::actualizarTemporizadores() {
	for (pair<const tipo_poder, int> &kv : temporizadorPoder) 
		if (kv.second > 0)
			kv.second -= frameDelay;
}

int ControladorPoderes::getTiempoRestante(tipo_poder poder) {
	return 
		temporizadorPoder[poder] > 0 ? 
			temporizadorPoder[poder] : 
			0;
}

bool ControladorPoderes::getEstaActivo(tipo_poder poder) {
	return (temporizadorPoder.count(poder) == 1 && temporizadorPoder[poder] > 0) ||
			(poderActivo.count(poder) == 1 && poderActivo[poder]);
}

void ControladorPoderes::activarPoder(tipo_poder poder, int temporizador) {
	if (temporizadorPoder.count(poder) == 1) 
		temporizadorPoder[poder] = temporizador;
	else 
		poderActivo[poder] = true;
}

void ControladorPoderes::desactivarPoder(tipo_poder poder) {
	if (temporizadorPoder.count(poder) == 1) {
		temporizadorPoder[poder] = 0;
	}
	else {
		poderActivo[poder] = false;
	}
}

void ControladorPoderes::desactivarPoderes() {
	for (pair<const tipo_poder, bool> &kv : poderActivo)
		kv.second = false;

	for (pair<const tipo_poder, int> &kv : temporizadorPoder) 
		kv.second = 0;
}
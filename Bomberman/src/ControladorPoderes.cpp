#include "../lib/ControladorPoderes.h"

map<tipo_poder, int> ControladorPoderes::poderActivo;
map<tipo_poder, int> ControladorPoderes::temporizadorPoder;

void ControladorPoderes::cargarPoderes() {
	temporizadorPoder[INMORTALIDAD] = 0;
	temporizadorPoder[BOMBAS_ATRAVIESAN_ESTRUCTURAS] = 0;
	poderActivo[AUMENTAR_VELOCIDAD] = 0;
	poderActivo[AUMENTAR_CANTIDAD_BOMBAS] = 0;
	poderActivo[AUMENTAR_ALCANCE_BOMBAS] = 0;
}

void ControladorPoderes::actualizarTemporizadores() {
	for (pair<const tipo_poder, int>& kv : temporizadorPoder)
		if (kv.second > 0)
			kv.second -= int(elapsed_time);
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
	return poderActivo.count(poder) == 1;
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

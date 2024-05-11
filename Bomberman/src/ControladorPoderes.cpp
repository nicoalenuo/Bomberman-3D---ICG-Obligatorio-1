#include "../lib/ControladorPoderes.h"

ControladorPoderes* ControladorPoderes::instancia = nullptr;

ControladorPoderes* ControladorPoderes::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorPoderes();
	return instancia;
}

ControladorPoderes::ControladorPoderes() {
	temporizadorPoder[INMORTALIDAD] = 0;
	temporizadorPoder[AUMENTAR_VELOCIDAD] = 0;
	poderActivo[BOMBAS_ATRAVIESAN_ESTRUCTURAS] = 0;
	poderActivo[AUMENTAR_CANTIDAD_BOMBAS] = 0;
	poderActivo[AUMENTAR_ALCANCE_BOMBAS] = 0;
}

void ControladorPoderes::resetearPoderes() {
	temporizadorPoder[INMORTALIDAD] = 0;
	temporizadorPoder[AUMENTAR_VELOCIDAD] = 0;
	poderActivo[BOMBAS_ATRAVIESAN_ESTRUCTURAS] = 0;
	poderActivo[AUMENTAR_CANTIDAD_BOMBAS] = 0;
	poderActivo[AUMENTAR_ALCANCE_BOMBAS] = 0;
}

void ControladorPoderes::actualizarTemporizadores() {
	for (pair<const tipo_poder, int>& kv : temporizadorPoder) {
		if (kv.second > 0)
			kv.second -= int(tiempo_entre_frames);
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

map<tipo_poder, int> ControladorPoderes::obtenerPoderes() {
	map<tipo_poder, int> poderes = map<tipo_poder, int>();
	for (int i = 0; i < static_cast<int>(BONIFICADOR_RANDOM); i++) {
		tipo_poder tipo = static_cast<tipo_poder>(i);
		if (temporizadorPoder.count(tipo) == 1) {
			poderes.insert(pair<tipo_poder, int>(tipo, temporizadorPoder[tipo]));
		}
		else {
			poderes.insert(pair<tipo_poder, int>(tipo, poderActivo[tipo]));
		}
	}
	return poderes;
}

ControladorPoderes::~ControladorPoderes() {

}
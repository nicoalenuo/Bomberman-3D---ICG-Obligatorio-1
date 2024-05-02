#include "../lib/ControladorPoderes.h"
#include "../lib/bomberman.h"

//enum tipo_poder { AUMENTAR_ALCANCE_BOMBAS, INMORTALIDAD, AUMENTAR_VELOCIDAD, BOMBAS_ATRAVIESAN_ESTRUCTURAS, AUMENTAR_CANTIDAD_BOMBAS, BONIFICADOR_RANDOM }
//para recordar cuales son los tipo_poder sin tener que ir al .h a cada rato

list<poder*> ControladorPoderes::poderes;

void ControladorPoderes::cargarPoderes() { //carga poderes al inicio de cada partida
	for (int i = 0; i < static_cast<int>(BONIFICADOR_RANDOM); i++) {
		poder* powerUp = new poder{ static_cast<tipo_poder>(i) ,0.f };
		poderes.push_back(powerUp);
	}
}

bool ControladorPoderes::poderDependeTiempo(tipo_poder poder) {
	return (poder == INMORTALIDAD || poder == AUMENTAR_VELOCIDAD);
}

bool ControladorPoderes::poderEsBooleano(tipo_poder poder) {
	return (poder == BOMBAS_ATRAVIESAN_ESTRUCTURAS); //aquí iria tmabien el MOVER_BOMBA
}

void ControladorPoderes::actualizarPoderes() { // cada vez que bomberman se actualiza, va a tener que llamar a esta funcion
	for (auto it = poderes.begin(); it != poderes.end(); ++it) {
		if (poderDependeTiempo((*it)->tipoPoder)){
			if ((*it)->valorPoder > 0) {
				(*it)->valorPoder -= frameDelay;
			}
			if ((*it)->valorPoder <= 0){
				(*it)->valorPoder = 0;
				if ((*it)->tipoPoder == AUMENTAR_VELOCIDAD) {
					jugador->setVelocidad(0.1f);
				}
			} 
		} 
	}
}

float ControladorPoderes::getValor(tipo_poder poder) {
	for (auto it = poderes.begin(); it != poderes.end(); ++it) {
		if ((*it)->tipoPoder == poder) {
			return (*it)->valorPoder;
		}
	}
	return 0; //no debería de llegar acá nunca
}

void ControladorPoderes::agregarPoder(tipo_poder poder) { //cuando el bonificador sea tocado por el bomberman, va a llamar a esta funcion
	float valor = 1;
	bool encontrado = false;
	if (poderDependeTiempo(poder)) {
		valor = 8000; //8000ms == 8 segundos
	}
	for (auto it = poderes.begin(); !encontrado && it != poderes.end(); ++it) {
		if ((*it)->tipoPoder == poder) {
			encontrado = true;
			switch (poder) {
				case AUMENTAR_ALCANCE_BOMBAS:
					(*it)->valorPoder = (*it)->valorPoder + valor;
					jugador->setLargoBomba((int) (*it)->valorPoder);
					break;
				case INMORTALIDAD:
					(*it)->valorPoder = valor;
					break;
				case AUMENTAR_VELOCIDAD:
					(*it)->valorPoder = valor;
					jugador->setVelocidad(0.2f);
					break;
				case BOMBAS_ATRAVIESAN_ESTRUCTURAS:
					(*it)->valorPoder = 1;
					break;
				case AUMENTAR_CANTIDAD_BOMBAS:
					(*it)->valorPoder = (*it)->valorPoder + valor;
					jugador->setMaxBomba((int) (*it)->valorPoder);
					break;
			}
		}
	}
}

bool ControladorPoderes::getEstaActivo(tipo_poder poder) {
	for (auto it = poderes.begin(); it != poderes.end(); ++it) {
		if ((*it)->tipoPoder == poder) {
			return (*it)->valorPoder > 0;
		}
	}
	return false;
}

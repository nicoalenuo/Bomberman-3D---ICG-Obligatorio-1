#include "../lib/particula.h"

particula::particula(vector_3 pos, vector_3 tam, vector_3 ac, vector_3 vel) : objeto(pos, tam) {
    eliminar = false;
    tiempoParticula = 0;
    pos_inicial = pos;
    aceleracion = ac;
    velocidad = vel;
}
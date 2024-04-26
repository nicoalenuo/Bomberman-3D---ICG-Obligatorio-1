#include "../lib/personaje.h"

personaje::personaje(vector_3 pos, vector_3 tam, GLfloat velocidad) : objeto(pos, tam) {
	this->velocidad = velocidad;
}

bool personaje::posicion_valida(vector_3 pos, vector_3 tam) {
    int largoTableroAux = largoTablero * int(tile_size);
    int anchoTableroAux = anchoTablero * int(tile_size);

    objeto* obj_1 = estructuras[int(pos.x - tam.x) / int(tile_size)][int(pos.z - tam.z) / int(tile_size)];
    objeto* obj_2 = estructuras[int(pos.x - tam.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];
    objeto* obj_3 = estructuras[int(pos.x + tam.x) / int(tile_size)][int(pos.z - tam.z) / int(tile_size)];
    objeto* obj_4 = estructuras[int(pos.x + tam.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];

    objeto* obj_5 = bombas[int(pos.x - tam.x) / int(tile_size)][int(pos.z - tam.z) / int(tile_size)];
    objeto* obj_6 = bombas[int(pos.x - tam.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];
    objeto* obj_7 = bombas[int(pos.x + tam.x) / int(tile_size)][int(pos.z - tam.z) / int(tile_size)];
    objeto* obj_8 = bombas[int(pos.x + tam.x) / int(tile_size)][int(pos.z + tam.z) / int(tile_size)];

    return
        pos.x - tam.x >= 0 &&
        pos.x + tam.x < largoTableroAux&&
        pos.z - tam.z >= 0 &&
        pos.z + tam.z < anchoTableroAux &&
        (obj_1 == nullptr || pos.x - tam.x < obj_1->getPosicion().x - obj_1->getTamanio().x || pos.x - tam.x > obj_1->getPosicion().x + obj_1->getTamanio().x || pos.z - tam.z < obj_1->getPosicion().z - obj_1->getTamanio().z || pos.z - tam.z > obj_1->getPosicion().z + obj_1->getTamanio().z) &&
        (obj_2 == nullptr || pos.x - tam.x < obj_2->getPosicion().x - obj_2->getTamanio().x || pos.x - tam.x > obj_2->getPosicion().x + obj_2->getTamanio().x || pos.z + tam.z < obj_2->getPosicion().z - obj_2->getTamanio().z || pos.z + tam.z > obj_2->getPosicion().z + obj_2->getTamanio().z) &&
        (obj_3 == nullptr || pos.x + tam.x < obj_3->getPosicion().x - obj_3->getTamanio().x || pos.x + tam.x > obj_3->getPosicion().x + obj_3->getTamanio().x || pos.z - tam.z < obj_3->getPosicion().z - obj_3->getTamanio().z || pos.z - tam.z > obj_3->getPosicion().z + obj_3->getTamanio().z) &&
        (obj_4 == nullptr || pos.x + tam.x < obj_4->getPosicion().x - obj_4->getTamanio().x || pos.x + tam.x > obj_4->getPosicion().x + obj_4->getTamanio().x || pos.z + tam.z < obj_4->getPosicion().z - obj_4->getTamanio().z || pos.z + tam.z > obj_4->getPosicion().z + obj_4->getTamanio().z) &&
        (obj_5 == nullptr || pos.x - tam.x < obj_5->getPosicion().x - obj_5->getTamanio().x || pos.x - tam.x > obj_5->getPosicion().x + obj_5->getTamanio().x || pos.z - tam.z < obj_5->getPosicion().z - obj_5->getTamanio().z || pos.z - tam.z > obj_5->getPosicion().z + obj_5->getTamanio().z) &&
        (obj_6 == nullptr || pos.x - tam.x < obj_6->getPosicion().x - obj_6->getTamanio().x || pos.x - tam.x > obj_6->getPosicion().x + obj_6->getTamanio().x || pos.z + tam.z < obj_6->getPosicion().z - obj_6->getTamanio().z || pos.z + tam.z > obj_6->getPosicion().z + obj_6->getTamanio().z) &&
        (obj_7 == nullptr || pos.x + tam.x < obj_7->getPosicion().x - obj_7->getTamanio().x || pos.x + tam.x > obj_7->getPosicion().x + obj_7->getTamanio().x || pos.z - tam.z < obj_7->getPosicion().z - obj_7->getTamanio().z || pos.z - tam.z > obj_7->getPosicion().z + obj_7->getTamanio().z) &&
        (obj_8 == nullptr || pos.x + tam.x < obj_8->getPosicion().x - obj_8->getTamanio().x || pos.x + tam.x > obj_8->getPosicion().x + obj_8->getTamanio().x || pos.z + tam.z < obj_8->getPosicion().z - obj_8->getTamanio().z || pos.z + tam.z > obj_8->getPosicion().z + obj_8->getTamanio().z);
}

bool personaje::contactoConFuego() {
    objeto* obj_1 = fuegos[getIndiceTablero(pos.x - tam.x)][getIndiceTablero(pos.z - tam.z)];
    objeto* obj_2 = fuegos[getIndiceTablero(pos.x - tam.x)][getIndiceTablero(pos.z + tam.z)];
    objeto* obj_3 = fuegos[getIndiceTablero(pos.x + tam.x)][getIndiceTablero(pos.z - tam.z)];
    objeto* obj_4 = fuegos[getIndiceTablero(pos.x + tam.x)][getIndiceTablero(pos.z + tam.z)];

    return (obj_1 != nullptr || obj_2 != nullptr || obj_3 != nullptr || obj_4 != nullptr);
}
#include "../lib/bomba.h"

bomba::bomba(vector_3 pos, vector_3 tam, int tiempo, int largo) : objeto(pos, tam) {
	tiempoBomba = tiempo;
	largoBomba = largo;
}

void bomba::actualizar() { // actualiza el tiempo, y si es cero, explota
   tiempoBomba -= frameDelay * velocidad_juego;
    if (this->tiempoBomba <= 0) {
        int x = getIndiceTablero(pos.x);
        int z = getIndiceTablero(pos.z);

        bool alcanza = false;
        for (int i = z+1; !alcanza && i < min(z + this->largoBomba + 1, anchoTablero); i++) { // x fijo, z incrementa
            if (ControladorPoderes::getEstaActivo(BOMBAS_ATRAVIESAN_ESTRUCTURAS) || estructuras[x][i] == nullptr) {
                if (fuegos[x][i] != nullptr)
                    delete fuegos[x][i];

                fuegos[x][i] = new fuego(
                    { GLfloat(x * tile_size) + tile_size / 2 , 0.0f, GLfloat(i * tile_size) + tile_size / 2 },
                    { tile_size / 2, tile_size, tile_size / 2 },
                    1500
                );
            }
            if (estructuras[x][i] != nullptr) {
                alcanza = !ControladorPoderes::getEstaActivo(BOMBAS_ATRAVIESAN_ESTRUCTURAS);
                estructura* est = dynamic_cast<estructura*>(estructuras[x][i]);
                if (est->getDestructible()) {
                    estructuras[x][i] = nullptr;
                    delete est;
                }
            }
        }

        alcanza = false;
        for (int i = z - 1; !alcanza && i >= max(z - this->largoBomba, 0); i--) { // x fijo, z decrementa
            if (ControladorPoderes::getEstaActivo(BOMBAS_ATRAVIESAN_ESTRUCTURAS) || estructuras[x][i] == nullptr) {
                if (fuegos[x][i] != nullptr)
                    delete fuegos[x][i];

                fuegos[x][i] = new fuego(
                    { GLfloat(x * tile_size) + tile_size / 2 , 0.0f, GLfloat(i * tile_size) + tile_size / 2 },
                    { tile_size / 2, tile_size, tile_size / 2 },
                    1500
                );
            }
            if (estructuras[x][i] != nullptr) {
                alcanza = !ControladorPoderes::getEstaActivo(BOMBAS_ATRAVIESAN_ESTRUCTURAS);
                estructura* est = dynamic_cast<estructura*>(estructuras[x][i]);
                if (est->getDestructible()) {
                    estructuras[x][i] = nullptr;
                    delete est;
                }
            }    
        }

        alcanza = false;
        for (int i = x + 1; !alcanza && i < min(x + this->largoBomba + 1, largoTablero); i++) { // z fijo, x incrementa
            if (ControladorPoderes::getEstaActivo(BOMBAS_ATRAVIESAN_ESTRUCTURAS) || estructuras[i][z] == nullptr) {
                if (fuegos[i][z] != nullptr)
                    delete fuegos[i][z];

                fuegos[i][z] = new fuego(
                    { GLfloat(i * tile_size) + tile_size / 2 , 0.0f, GLfloat(z * tile_size) + tile_size / 2 },
                    { tile_size / 2, tile_size, tile_size / 2 },
                    1500
                );
            }
            if (estructuras[i][z] != nullptr) {
                alcanza = !ControladorPoderes::getEstaActivo(BOMBAS_ATRAVIESAN_ESTRUCTURAS);
                estructura* est = dynamic_cast<estructura*>(estructuras[i][z]);
                if (est->getDestructible()) {
                    estructuras[i][z] = nullptr;
                    delete est;
                }
            }
        }

        alcanza = false;
        for (int i = x - 1; !alcanza && i >= max(x - this->largoBomba, 0); i--) { // z fijo, x decrementa
            if (ControladorPoderes::getEstaActivo(BOMBAS_ATRAVIESAN_ESTRUCTURAS) || estructuras[i][z] == nullptr) {
                if (fuegos[i][z] != nullptr)
                    delete fuegos[i][z];

                fuegos[i][z] = new fuego(
                    { GLfloat(i * tile_size) + tile_size / 2 , 0.0f, GLfloat(z * tile_size) + tile_size / 2 },
                    { tile_size / 2, tile_size, tile_size / 2 },
                    1500
                );
            }
            if (estructuras[i][z] != nullptr) {
                alcanza = !ControladorPoderes::getEstaActivo(BOMBAS_ATRAVIESAN_ESTRUCTURAS);
                estructura* est = dynamic_cast<estructura*>(estructuras[i][z]);
                if (est->getDestructible()) {
                    estructuras[i][z] = nullptr;
                    delete est;
                }
            } 
        }

        fuegos[x][z] = new fuego(
            { GLfloat(x * tile_size) + tile_size / 2 , 0.0f, GLfloat(z * tile_size) + tile_size / 2 },
            { tile_size / 2, tile_size, tile_size / 2 },
              1500
        ); 

        jugador->disminuirCantBomba();

        ControladorCamara::sacudir(1000);

        bombas[x][z] = nullptr;
        delete this;
    } 
}

void bomba::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    ControladorObjetos::dibujar(OBJ_BOMBA);
    glPopMatrix();
}
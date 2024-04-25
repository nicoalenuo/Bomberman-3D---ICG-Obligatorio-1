#include "../lib/bomba.h"

bomba::bomba(vector_3 pos, vector_3 tam, int tiempo, int largo) : objeto(pos, tam) {
	this->tiempoBomba = tiempo;
	this->largoBomba = largo;
}

void bomba::actualizar() { // actualiza el tiempo, y si es cero, explota
   tiempoBomba -= frameDelay * velocidad_juego;
    if (this->tiempoBomba <= 0) {
        int x = getPosicionXEnTablero(pos.x);
        int z = getPosicionZEnTablero(pos.z);

        bool alcanza = false;

        for (int i = z+1; !alcanza && i < min(z + this->largoBomba + 1, anchoTablero); i++) { // x fijo, z incrementa
            if (estructuras[x][i] != nullptr) { // por ahora no toma en cuenta jugador
                alcanza = true;
                estructura* est = dynamic_cast<estructura*>(estructuras[x][i]);
                if (est->getDestructible()) {
                    delete est;
                    estructuras[x][i] = nullptr;
                }
            }
            else {
                if (fuegos[x][i] != nullptr)
                    delete fuegos[x][i];

                fuegos[x][i] = new fuego(
                    { GLfloat(x * tile_size) + tile_size / 2 , 0.5, GLfloat(i * tile_size) + tile_size / 2 },
                    { tile_size / 2, tile_size, tile_size / 2 },
                    2000
                );
            }

            if (bombas[x][i] != nullptr) {
                bomba* bomb = dynamic_cast<bomba*>(bombas[x][i]);
                bomb->setTiempoBomba(0);
            }
            if (bonificadores[x][i] != nullptr) {
                delete bonificadores[x][i];
                bonificadores[x][i] = nullptr;
            }
        }

        alcanza = false;
        for (int i = z - 1; !alcanza && i >= max(z - this->largoBomba, 0); i--) { // x fijo, z decrementa
            if (estructuras[x][i] != nullptr) { 
                alcanza = true;
                estructura* est = dynamic_cast<estructura*>(estructuras[x][i]);
                if (est->getDestructible()) {
                    delete est;
                    estructuras[x][i] = nullptr;
                }
            }
            else {
                if (fuegos[x][i] != nullptr)
                    delete fuegos[x][i];

                fuegos[x][i] = new fuego(
                    { GLfloat(x * tile_size) + tile_size / 2 , 0.5, GLfloat(i * tile_size) + tile_size / 2 },
                    { tile_size / 2, tile_size, tile_size / 2 },
                    2000
                );
            }
            if (bombas[x][i] != nullptr) {
                bomba* bomb = dynamic_cast<bomba*>(bombas[x][i]);
                bomb->setTiempoBomba(0);
            }
            if (bonificadores[x][i] != nullptr) {
                delete bonificadores[x][i];
                bonificadores[x][i] = nullptr;
            }
        }

        alcanza = false;
        for (int i = x + 1; !alcanza && i < min(x + this->largoBomba + 1, largoTablero); i++) { // z fijo, x incrementa
            if (estructuras[i][z] != nullptr) {
                alcanza = true;
                estructura* est = dynamic_cast<estructura*>(estructuras[i][z]);
                if (est->getDestructible()) {
                    delete est;
                    estructuras[i][z] = nullptr;
                }
            }
            else {
                if (fuegos[i][z] != nullptr)
                    delete fuegos[i][z];

                fuegos[i][z] = new fuego(
                    { GLfloat(i * tile_size) + tile_size / 2 , 0.5, GLfloat(z * tile_size) + tile_size / 2 },
                    { tile_size / 2, tile_size, tile_size / 2 },
                    2000
                );
            }
            if (bombas[i][z] != nullptr) {
                bomba* bomb = dynamic_cast<bomba*>(bombas[i][z]);
                bomb->setTiempoBomba(0);
            }
            if (bonificadores[i][z] != nullptr) {
                delete bonificadores[x][i];
                bonificadores[i][z] = nullptr;
            }
        }

        alcanza = false;
        for (int i = x - 1; !alcanza && i >= max(x - this->largoBomba, 0); i--) { // z fijo, x decrementa
            if (estructuras[i][z] != nullptr) {
                alcanza = true;
                estructura* est = dynamic_cast<estructura*>(estructuras[i][z]);
                if (est->getDestructible()) {
                    delete est;
                    estructuras[i][z] = nullptr;
                }
            }
            else {
                if (fuegos[i][z] != nullptr)
                    delete fuegos[i][z];

                fuegos[i][z] = new fuego(
                    { GLfloat(i * tile_size) + tile_size / 2 , 0.5, GLfloat(z * tile_size) + tile_size / 2 },
                    { tile_size / 2, tile_size, tile_size / 2 }, 
                      2000
                );
            }
            if (bombas[i][z] != nullptr) {
                bomba* bomb = dynamic_cast<bomba*>(bombas[i][z]);
                bomb->setTiempoBomba(0);
            }
            if (bonificadores[i][z] != nullptr) {
                delete bonificadores[x][i];
                bonificadores[i][z] = nullptr;
            }
        }

        fuegos[x][z] = new fuego(
            { GLfloat(x * tile_size) + tile_size / 2 , 0.5, GLfloat(z * tile_size) + tile_size / 2 },
            { tile_size / 2, tile_size, tile_size / 2 },
              3000 //Hago que dure un poquito mas//Hago que dure un poquito mas
        ); 

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
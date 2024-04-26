#include "../lib/bomba.h"

bomba::bomba(vector_3 pos, vector_3 tam, int tiempo, int largo,bomberman* jug) : objeto(pos, tam) {
	this->tiempoBomba = tiempo;
	this->largoBomba = largo;
}

void bomba::actualizar() { // actualiza el tiempo, y si es cero, explota
   tiempoBomba -= frameDelay * velocidad_juego;
   int x = getPosicionXEnTablero(pos.x, tam.x);
   int z = getPosicionZEnTablero(pos.z, tam.z);

    if (this->tiempoBomba <= 0 || (fuegos[x][z] != nullptr)) {
        int xJugador = getPosicionXEnTablero(jugador->getPosicion().x, jugador->getTamanio().x);
        int zJugador = getPosicionZEnTablero(jugador->getPosicion().z, jugador->getTamanio().z);

        bool alcanza = false;

        for (int i = z+1; !alcanza && i < min(z + this->largoBomba + 1, anchoTablero); i++) { // x fijo, z incrementa
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
                    1500
                );
            }

            if (bombas[x][i] != nullptr) {
                alcanza = true;
                bomba* bomb = dynamic_cast<bomba*>(bombas[x][i]);
                bomb->setTiempoBomba(0);
            }

            if (!inmortal && xJugador == x && zJugador == i) {
                finJuego = true;
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
                    1500
                );
            }
            if (bombas[x][i] != nullptr) {
                alcanza = true;
                bomba* bomb = dynamic_cast<bomba*>(bombas[x][i]);
                bomb->setTiempoBomba(0);
            }

            if (!inmortal &&  xJugador == x && zJugador == i) {
                finJuego = true;
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
                    1500
                );
            }
            if (bombas[i][z] != nullptr) {
                alcanza = true;
                bomba* bomb = dynamic_cast<bomba*>(bombas[i][z]);
                bomb->setTiempoBomba(0);
            }

            if (!inmortal &&  xJugador == i && zJugador == z) {
                finJuego = true;
                cout << finJuego << endl;
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
            } else {
                if (fuegos[i][z] != nullptr)
                    delete fuegos[i][z];

                fuegos[i][z] = new fuego(
                    { GLfloat(i * tile_size) + tile_size / 2 , 0.5, GLfloat(z * tile_size) + tile_size / 2 },
                    { tile_size / 2, tile_size, tile_size / 2 }, 
                    1500
                );
            }
            if (bombas[i][z] != nullptr) {
                alcanza = true;
                bomba* bomb = dynamic_cast<bomba*>(bombas[i][z]);
                bomb->setTiempoBomba(0);
            }

            if (!inmortal &&  xJugador == i && zJugador == z) {
                finJuego = true;
                cout << finJuego << endl;
            }
        }

        fuegos[x][z] = new fuego(
            { GLfloat(x * tile_size) + tile_size / 2 , 0.5, GLfloat(z * tile_size) + tile_size / 2 },
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
    glEnable(GL_TEXTURE_2D);
    glTranslatef(pos.x, pos.y, pos.z);
    ControladorObjetos::dibujar(OBJ_BOMBA);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
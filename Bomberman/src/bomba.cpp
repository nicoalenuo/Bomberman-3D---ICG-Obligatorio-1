#include "../lib/bomba.h"

bomba::bomba(vector_3 pos, vector_3 tam, int tiempo, int largo, int id) : objeto(pos, tam) {
	tiempoBomba = tiempo;
	largoBomba = largo;
    scale = 0.9f;
    cayendo = true;
    idSonido = id;
}

int xBomba, zBomba, dx, dz, nx, nz;
void bomba::actualizar() {
    scale += GLfloat(0.005f * (elapsed_time / frameDelay));

    if (cayendo && pos.y > 0.0f) {
        pos.y -= 0.05f;

        if (pos.y <= 0.0f) {
            pos.y = 0;
            cayendo = false;

            random_device rdVelocidadParticulaTierra;
            mt19937 genVelocidadParticulaTierra(rdVelocidadParticulaTierra());
            uniform_real_distribution<> disVelocidadParticulaTierra(-0.2, 0.2);

            for (int i = 0; i < 40; i++) {
                particulas.push_back(new particula_tierra(
                    pos,
                    { GLfloat(0.05f), GLfloat(0.05f), GLfloat(0.05f) },
                    { 0, -25, 0 },
                    { GLfloat(disVelocidadParticulaTierra(genVelocidadParticulaTierra)), 5, GLfloat(disVelocidadParticulaTierra(genVelocidadParticulaTierra)) },
                    ControladorTexturas::getTextura(TEXTURA_SUELO)
                    )
                );
            }
        }
    }

    tiempoBomba -= int(elapsed_time);
    bool alcanza;
    if (tiempoBomba <= 0) {
        xBomba = getIndiceTablero(pos.x);
        zBomba = getIndiceTablero(pos.z);

        for (int dir = 0; dir < 4; dir++) {
            dx = 0;
            dz = 0;
            alcanza = false;

            if (dir == 0)  // z fijo, x incrementa
                dx = 1;
            else if (dir == 1)  // z fijo, x decrementa
                dx = -1;
            else if (dir == 2)  // x fijo, z incrementa
                dz = 1;
            else if (dir == 3)  // x fijo, z decrementa
                dz = -1;

            for (int i = 1; i <= largoBomba && !alcanza; i++) {
                nx = xBomba + i * dx;
                nz = zBomba + i * dz;

                if (nx >= 0 && nx < largoTablero && nz >= 0 && nz < anchoTablero) {
                    if (estructuras[nx][nz] == nullptr || (ControladorPoderes::getValor(BOMBAS_ATRAVIESAN_ESTRUCTURAS) && dynamic_cast<estructura*>(estructuras[nx][nz])->getDestructible())) {
                        if (fuegos[nx][nz] != nullptr)
                            delete fuegos[nx][nz];

                        fuegos[nx][nz] = new fuego(
                            { GLfloat(nx * tile_size) + tile_size / 2 , 0.0f, GLfloat(nz * tile_size) + tile_size / 2 },
                            { tile_size / 2, tile_size, tile_size / 2 },
                            1500,
                            false
                        );
                    }

                    if (estructuras[nx][nz] != nullptr) {
                        alcanza = !ControladorPoderes::getValor(BOMBAS_ATRAVIESAN_ESTRUCTURAS);
                        estructura* est = dynamic_cast<estructura*>(estructuras[nx][nz]);
                        if (est->getDestructible()) {
                            delete est;
                            if (estructuras[nx][nz] != nullptr) {
                                cout << "aloh?" << endl;
                            }
                            estructuras[nx][nz] = nullptr;
                        }
                    }
                }
                else {
                    alcanza = true; 
                }
            }
        }

        if (fuegos[xBomba][zBomba] != nullptr) 
            delete fuegos[xBomba][zBomba];

        fuegos[xBomba][zBomba] = new fuego(
            { GLfloat(xBomba * tile_size) + tile_size / 2 , 0.0f, GLfloat(zBomba * tile_size) + tile_size / 2 },
            { tile_size / 2, tile_size, tile_size / 2 },
            1500,
            true
        );

        ControladorAudio::detenerMecha(idSonido);
        ControladorAudio::playBomba(pos);

        jugador->disminuirCantBomba();

        ControladorCamara::sacudir(1000);

        bombas[xBomba][zBomba] = nullptr;
        delete this;
    }
}


void bomba::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glScalef(scale, scale, scale);
    ControladorObjetos::dibujar(OBJ_BOMBA);
    glPopMatrix();
}
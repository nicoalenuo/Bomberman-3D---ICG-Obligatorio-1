#include "../lib/bomba.h"

bomba::bomba(posicion pos, tamanio tam, int tiempo, int largo) : objeto(pos, tam) {
	this->tiempoBomba = tiempo;
	this->largoBomba = largo;
}


random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(-0.3, 0.3);

void bomba::actualizar() { // actualiza el tiempo, y si es cero, explota
   tiempoBomba -= frameDelay;
    if (this->tiempoBomba <= 0) {
        int x = getPosicionXEnTablero(pos.x, tam.x);
        int z = getPosicionZEnTablero(pos.z, tam.z);

        bool alcanza = false;

        for (int i = z+1; !alcanza && i < min(z + this->largoBomba + 1, anchoTablero); i++) { // x fijo, z incrementa
            if (estructuras[x][i] != nullptr) { // por ahora no toma en cuenta jugador
                alcanza = true;
                estructura* est = dynamic_cast<estructura*>(estructuras[x][i]);
                if (est->getDestructible()) { //Pasarle un mensaje a la estructura para que comience la animacion de destruccion, 
                    delete estructuras[x][i];
                    estructuras[x][i] = nullptr;

                    for (int j = 0; j < 80; j++) {
                        particulas.push_back(
                            new particula(
                                { x * tile_size + tile_size / 2, tile_size / 2, i * tile_size + tile_size / 2 },
                                { 0.07, 0.07, 0.07 },
                                { 0, -25, 0 },
                                { GLfloat(dis(gen)), 10, GLfloat(dis(gen)) }
                            )
                        );
                    }
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
        }

        alcanza = false;
        for (int i = z - 1; !alcanza && i >= max(z - this->largoBomba, 0); i--) { // x fijo, z decrementa
            if (estructuras[x][i] != nullptr) { // por ahora no toma en cuenta jugador
                alcanza = true;
                estructura* est = dynamic_cast<estructura*>(estructuras[x][i]);
                if (est->getDestructible()) {
                    delete estructuras[x][i];
                    estructuras[x][i] = nullptr;

                    for (int j = 0; j < 80; j++) {
                        particulas.push_back(
                            new particula(
                                { x * tile_size + tile_size / 2, tile_size / 2, i * tile_size + tile_size / 2 },
                                { 0.07, 0.07, 0.07 },
                                { 0, -25, 0 },
                                { GLfloat(dis(gen)), 10, GLfloat(dis(gen)) }
                            )
                        );
                    }
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
        }

        alcanza = false;
        for (int i = x + 1; !alcanza && i < min(x + this->largoBomba + 1, largoTablero); i++) { // z fijo, x incrementa
            if (estructuras[i][z] != nullptr) { // por ahora no toma en cuenta jugador
                alcanza = true;
                estructura* est = dynamic_cast<estructura*>(estructuras[i][z]);
                if (est->getDestructible()) {
                    delete estructuras[i][z];
                    estructuras[i][z] = nullptr;

                    for (int j = 0; j < 80; j++) {
                        particulas.push_back(
                            new particula(
                                { i * tile_size + tile_size / 2, tile_size / 2, z * tile_size + tile_size / 2 },
                                { 0.07, 0.07, 0.07 },
                                { 0, -25, 0 },
                                { GLfloat(dis(gen)), 10, GLfloat(dis(gen)) }
                            )
                        );
                    }
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
        }

        alcanza = false;
        for (int i = x - 1; !alcanza && i >= max(x - this->largoBomba, 0); i--) { // z fijo, x decrementa
            if (estructuras[i][z] != nullptr) { // por ahora no toma en cuenta jugador
                alcanza = true;
                estructura* est = dynamic_cast<estructura*>(estructuras[i][z]);
                if (est->getDestructible()) {
                    delete estructuras[i][z];
                    estructuras[i][z] = nullptr;

                    for (int j = 0; j < 80; j++) {
                        particulas.push_back(
                            new particula(
                                { i * tile_size + tile_size / 2, tile_size / 2, z * tile_size + tile_size / 2 },
                                { 0.07, 0.07, 0.07 },
                                { 0, -25, 0 },
                                { GLfloat(dis(gen)), 10, GLfloat(dis(gen)) }
                            )
                        );
                    }
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
        }

        fuegos[x][z] = new fuego(
            { GLfloat(x * tile_size) + tile_size / 2 , 0.5, GLfloat(z * tile_size) + tile_size / 2 },
            { tile_size / 2, tile_size, tile_size / 2 },
              3000 //Hago que dure un poquito mas//Hago que dure un poquito mas
        ); 

        bombas[x][z] = nullptr;
        delete this;
    } 
}

void bomba::dibujar() {
    glPushMatrix();

    glTranslatef(pos.x, pos.y, pos.z);
    glBegin(GL_QUADS);

    glColor3f(1.0, 1.0, 1.0);

    glVertex3f(-tam.x, 0, -tam.z);
    glVertex3f(tam.x, 0, -tam.z);
    glVertex3f(tam.x, 0, tam.z);
    glVertex3f(-tam.x, 0, tam.z);

    // Cara de arriba
    glVertex3f(-tam.x, tam.y, -tam.z);
    glVertex3f(tam.x, tam.y, -tam.z);
    glVertex3f(tam.x, tam.y, tam.z);
    glVertex3f(-tam.x, tam.y, tam.z);

    // Cara de atras
    glVertex3f(-tam.x, 0, -tam.z);
    glVertex3f(tam.x, 0, -tam.z);
    glVertex3f(tam.x, tam.y, -tam.z);
    glVertex3f(-tam.x, tam.y, -tam.z);

    // Cara de adelante
    glVertex3f(-tam.x, 0, tam.z);
    glVertex3f(tam.x, 0, tam.z);
    glVertex3f(tam.x, tam.y, tam.z);
    glVertex3f(-tam.x, tam.y, tam.z);

    // Cara izquierda
    glVertex3f(-tam.x, 0, -tam.z);
    glVertex3f(-tam.x, 0, tam.z);
    glVertex3f(-tam.x, tam.y, tam.z);
    glVertex3f(-tam.x, tam.y, -tam.z);

    // Cara derecha
    glVertex3f(tam.x, 0, -tam.z);
    glVertex3f(tam.x, 0, tam.z);
    glVertex3f(tam.x, tam.y, tam.z);
    glVertex3f(tam.x, tam.y, -tam.z);
    glEnd();
    glPopMatrix();
}

int bomba::getTiempoBomba() {
    return this->tiempoBomba;
}

void bomba::setTiempoBomba(int tiempo) {
    this->tiempoBomba = tiempo;
}

int bomba::getLargoBomba() {
    return this->largoBomba;
}

void bomba::setLargoBomba(int largo) {
    this->largoBomba = largo;
}
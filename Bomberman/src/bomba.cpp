#include "../lib/bomba.h"
#include "../lib/controlador.h"

bomba::bomba(posicion pos, tamanio tam, int tiempo, int largo) : objeto(pos, tam) {
	this->tiempoBomba = tiempo;
	this->largoBomba = largo;
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


void bomba::actualizar() { // actualiza el tiempo, y si es cero, explota

    tiempoBomba -= frameDelay;
    if (this->tiempoBomba <= 0) {
        Controlador* controlador = Controlador::getInstance();
        objeto*** estructuras = controlador->getEstructuras();
        objeto*** bombas = controlador->getBombas();
        objeto*** fuegos = controlador->getFuegos();

        int largoEstructuras = controlador->getLargoTablero();
        int anchoEstructuras = controlador->getAnchoTablero();

        int x = controlador->getPosicionXEnTablero(pos.x, tam.x);
        int z = controlador->getPosicionZEnTablero(pos.z, tam.z);

        bool alcanza = false;

        for (int i = z+1; !alcanza && i < min(z + this->largoBomba + 1, anchoEstructuras); i++) { // x fijo, z incrementa
            if (estructuras[x][i] != nullptr) { // por ahora no toma en cuenta jugador
                alcanza = true;
                estructura* est = dynamic_cast<estructura*>(estructuras[x][i]);
                if (est->getDestructible()) { //Pasarle un mensaje a la estructura para que comience la animacion de destruccion, 
                    delete estructuras[x][i];
                    estructuras[x][i] = nullptr;
                }
            }
            else {
                if (fuegos[x][i] != nullptr) {
                    delete fuegos[x][i];
                }
                fuegos[x][i] = new fuego({ GLfloat(x * tile_size) , 0.5, GLfloat(i * tile_size)}, {GLfloat(tile_size), GLfloat(tile_size), GLfloat(tile_size)}, 2000);
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
                }
            }
            else {
                if (fuegos[x][i] != nullptr) {
                    delete fuegos[x][i];
                }
                fuegos[x][i] = new fuego({ GLfloat(x * tile_size) , 0.5, GLfloat(i * tile_size) }, { GLfloat(tile_size), GLfloat(tile_size), GLfloat(tile_size) }, 2000);
            }
        }

        alcanza = false;
        for (int i = x + 1; !alcanza && i < min(x + this->largoBomba + 1, largoEstructuras); i++) { // z fijo, x incrementa
            if (estructuras[i][z] != nullptr) { // por ahora no toma en cuenta jugador
                alcanza = true;
                estructura* est = dynamic_cast<estructura*>(estructuras[i][z]);
                if (est->getDestructible()) {
                    delete estructuras[i][z];
                    estructuras[i][z] = nullptr;
                }
            }
            else {
                if (fuegos[i][z] != nullptr) {
                    delete fuegos[i][z];
                }
                fuegos[i][z] = new fuego({ GLfloat(i * tile_size) , 0.5, GLfloat(z * tile_size) }, { GLfloat(tile_size), GLfloat(tile_size), GLfloat(tile_size) }, 2000);
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
                }
            }
            else {
                if (fuegos[i][z] != nullptr) {
                    delete fuegos[i][z];
                }
                fuegos[i][z] = new fuego({ GLfloat(i * tile_size) , 0.5, GLfloat(z * tile_size) }, { GLfloat(tile_size), GLfloat(tile_size), GLfloat(tile_size) }, 2000);
            }
        }

        fuegos[x][z] = new fuego({ GLfloat(x * tile_size) , 0.5, GLfloat(z * tile_size) }, { GLfloat(tile_size), GLfloat(tile_size), GLfloat(tile_size) }, 3000); //Hago que dure un poquito mas
        bombas[x][z] = nullptr;
        delete this;
    } 
}

void bomba::dibujar() {
    glPushMatrix();

    glTranslatef(pos.x, pos.y, pos.z);
    glBegin(GL_QUADS);


    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0, 0, 0);
    glVertex3f(tam.x, 0, 0);
    glVertex3f(tam.x, 0, tam.z);
    glVertex3f(0, 0, tam.z);

    // Cara de arriba
    glVertex3f(0, tam.y, 0);
    glVertex3f(tam.x, tam.y, 0);
    glVertex3f(tam.x, tam.y, tam.z);
    glVertex3f(0, tam.y, tam.z);

    // Cara de atras
    glVertex3f(0, 0, 0);
    glVertex3f(tam.x, 0, 0);
    glVertex3f(tam.x, tam.y, 0);
    glVertex3f(0, tam.y, 0);

    // Cara de adelante
    glVertex3f(0, 0, tam.z);
    glVertex3f(tam.x, 0, tam.z);
    glVertex3f(tam.x, tam.y, tam.z);
    glVertex3f(0, tam.y, tam.z);

    // Cara izquierda
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, tam.z);
    glVertex3f(0, tam.y, tam.z);
    glVertex3f(0, tam.y, 0);

    // Cara derecha (x = 1)
    glVertex3f(tam.x, 0, 0);
    glVertex3f(tam.x, 0, tam.z);
    glVertex3f(tam.x, tam.y, tam.z);
    glVertex3f(tam.x, tam.y, 0);
    glEnd();
    glPopMatrix();
}
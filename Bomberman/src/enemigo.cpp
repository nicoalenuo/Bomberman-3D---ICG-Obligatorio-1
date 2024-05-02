#include "../lib/enemigo.h"

enemigo::enemigo(vector_3 pos, vector_3 tam): personaje(pos, tam, GLfloat(0.1)){
	orientacionX = true;
    moverX = true;
    moverNX = false;
    moverZ = false;
    moverNZ = false;
    
    eliminar = false;

    probCambiarPos = 0.3;
}

enemigo::enemigo(vector_3 pos, vector_3 tam, bool orientacionX) : personaje(pos, tam, GLfloat(0.1)) {
    this->orientacionX = orientacionX;
    if (orientacionX) {
        moverX = true;
        moverNX = false;
        moverZ = false;
        moverNZ = false;
    } else {
        moverX = false;
        moverNX = false;
        moverZ = true;
        moverNZ = false;
    }
    
    eliminar = false;

    probCambiarPos = 0.3;
}

bool enemigo::getOrientacionX() {
    return orientacionX;
}

void enemigo::setOrientacionX(bool orientacionX) {
    this->orientacionX = orientacionX;
    if (orientacionX) {
        moverX = true;
        moverNX = false;
        moverZ = false;
        moverNZ = false;
    } else {
        moverX = false;
        moverNX = false;
        moverZ = true;
        moverNZ = false;
    }
}

bool enemigo::intersecta(bomberman* b) {
    return pos.x < b->getPosicion().x + b->getTamanio().x &&
        pos.x + tam.x > b->getPosicion().x &&
        pos.z < b->getPosicion().z + b->getTamanio().z &&
        pos.z + tam.z > b->getPosicion().z;
}

bool centroConMovimiento(vector_3 pos) {
    return abs(round(pos.x - tile_size / 2) - (pos.x - tile_size / 2)) < 0.001 &&
           abs(round(pos.z - tile_size / 2) - (pos.z - tile_size / 2)) < 0.001 &&
           getIndiceTablero(pos.x) % 2 == 0 && 
           getIndiceTablero(pos.z) % 2 == 0;
}

bool posicion_valida_parcial(vector_3 pos, bool orientacionX) {
    int largoTableroAux = largoTablero * int(tile_size);
    int anchoTableroAux = anchoTablero * int(tile_size);

    int x,z,p,n;
    x = getIndiceTablero(pos.x);
    z = getIndiceTablero(pos.z);

    objeto *obj_1, *obj_2, *obj_3, *obj_4 = nullptr;

    if (orientacionX) {
        p = min(x + 1, largoTablero);
        n = max(x - 1, 0);
        obj_1 = estructuras[p][z];
        obj_2 = estructuras[n][z];
        obj_3 = bombas[p][z];
        obj_4 = bombas[n][z];
    } else {
        p = min(z + 1, anchoTablero);
        n = max(z - 1, 0);
        obj_1 = estructuras[x][p];
        obj_2 = estructuras[x][n];
        obj_3 = bombas[x][p];
        obj_4 = bombas[x][n];
    }

    return
        (obj_1 == nullptr && obj_3 == nullptr) ||
        (obj_2 == nullptr && obj_4 == nullptr);
}


void enemigo::actualizar() {
    bool cambio = false;
    //probablemente deba cambiar de lugar
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    GLfloat desplazamiento = velocidad * (elapsed_time / frameDelay);

    if (orientacionX) {
        if (centroConMovimiento(pos) && (dis(gen) < probCambiarPos) && posicion_valida_parcial(pos, false)) {
            //falta corregir, al usar centroConMovimiento me toma en cuenta no solo los centros si no tambien las aristas
            //por eso a veces hace un movimineto extranio entre dos esquinas, lo voy a corregir despues @victor
            moverX = false;
            moverNX = false;
            moverZ = dis(gen) < probCambiarPos;
            moverNZ = !moverZ;
            orientacionX = false;
            cambio = true;
        }
        if (moverX) {
            if (posicion_valida({ pos.x + desplazamiento, 0, pos.z }, { tam.x, 0, tam.z })) {
                pos.x += desplazamiento;
            } else {
                moverX = false;
                moverNX = true;
            }
        }
        if (moverNX) {
            if (posicion_valida({ pos.x - desplazamiento, 0, pos.z }, { tam.x, 0, tam.z })) {
                pos.x -= desplazamiento;
            } else {
                moverX = true;
                moverNX = false;
            }
        }
    }
    if (!orientacionX) {
        if (!cambio && centroConMovimiento(pos) && (dis(gen) < probCambiarPos) && posicion_valida_parcial(pos, true)) {
            moverX = dis(gen) < probCambiarPos;
            moverNX = !moverX;
            moverZ = false;
            moverNZ = false;
            orientacionX = true;
        }
        if (moverZ) {
            if (posicion_valida({ pos.x, 0, pos.z + desplazamiento }, { tam.x, 0, tam.z })) {
                pos.z += desplazamiento;
            }
            else {
                moverZ = false;
                moverNZ = true;
            }
        }
        if (moverNZ) {
            if (posicion_valida({ pos.x, 0, pos.z - desplazamiento }, { tam.x, 0, tam.z })) {
                pos.z -= desplazamiento;
            }
            else {
                moverZ = true;
                moverNZ = false;
            }
        }
    }

    if (contactoConFuego())
        eliminar = true;
}

void enemigo::dibujar() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);

    /*if (texturas_habilitadas) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ControladorTexturas::getTextura(TEXTURA_PUERTA));
    }*/

    glColor3f(1.0f, 0.5f, 0.f);

    glBegin(GL_QUADS);

    //Cara de abajo
    //glTexCoord2f(0.5, 0.5);
    glVertex3f(-tam.x, 0, -tam.z);

    //glTexCoord2f(0.5, 1);
    glVertex3f(tam.x, 0, -tam.z);

    //glTexCoord2f(1, 1);
    glVertex3f(tam.x, 0, tam.z);

    //glTexCoord2f(1, 0.5);
    glVertex3f(-tam.x, 0, tam.z);

    // Cara de arriba
    //glTexCoord2f(0.5, 0.5);
    glVertex3f(-tam.x, tam.y, -tam.z);

    //glTexCoord2f(0.5, 1);
    glVertex3f(tam.x, tam.y, -tam.z);

    //glTexCoord2f(1, 1);
    glVertex3f(tam.x, tam.y, tam.z);

    //glTexCoord2f(1, 0.5);
    glVertex3f(-tam.x, tam.y, tam.z);

    // Cara de atras
    //glTexCoord2f(1, 0);
    glVertex3f(-tam.x, 0, -tam.z);

    //glTexCoord2f(0.5, 0);
    glVertex3f(tam.x, 0, -tam.z);

    //glTexCoord2f(0.5, 0.5);
    glVertex3f(tam.x, tam.y, -tam.z);

    //glTexCoord2f(1, 0.5);
    glVertex3f(-tam.x, tam.y, -tam.z);

    // Cara de adelante
    //glTexCoord2f(0.5, 0);
    glVertex3f(-tam.x, 0, tam.z);

    //glTexCoord2f(0, 0);
    glVertex3f(tam.x, 0, tam.z);

    //glTexCoord2f(0, 0.5);
    glVertex3f(tam.x, tam.y, tam.z);

    //glTexCoord2f(0.5, 0.5);
    glVertex3f(-tam.x, tam.y, tam.z);

    // Cara izquierda
    //glTexCoord2f(0.5, 0);
    glVertex3f(-tam.x, 0, -tam.z);

    //glTexCoord2f(0, 0);
    glVertex3f(-tam.x, 0, tam.z);

    //glTexCoord2f(0, 0.5);
    glVertex3f(-tam.x, tam.y, tam.z);

    //glTexCoord2f(0.5, 0.5);
    glVertex3f(-tam.x, tam.y, -tam.z);

    // Cara derecha (x = 1)
    //glTexCoord2f(0.5, 0);
    glVertex3f(tam.x, 0, -tam.z);

    //glTexCoord2f(0, 0);
    glVertex3f(tam.x, 0, tam.z);

    //glTexCoord2f(0, 0.5);
    glVertex3f(tam.x, tam.y, tam.z);

    //glTexCoord2f(0.5, 0.5);
    glVertex3f(tam.x, tam.y, -tam.z);

    glEnd();

    //if (texturas_habilitadas)
    //tg    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
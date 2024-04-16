#include "../lib/estructura.h"
#include "../lib/controlador.h"

estructura::estructura(GLfloat x, GLfloat z, bool dest) : objeto(x,z) {
	this->destructible = dest;
	this->powerUp = nullptr;

	global = global::getInstance();
}

bool estructura::getDestructible() {
	return this->destructible;
}

void estructura::setDestructible(bool dest) {
	this->destructible = dest;
}

bonificador* estructura::getPowerUp() {
	return this->powerUp;
}

void estructura::setPowerUp(bonificador* power) {
	this->powerUp = power;
}

void estructura::actualizar() {
	if (this->destructible) {
		//si es destructible entonces hace cosas en actualizar
	}
}

void estructura::dibujar() {
    Controlador* controlador = Controlador::getInstance();
    bool textura = controlador->getTextura();
    if (textura) {
        estructura* est = dynamic_cast<estructura*>(controlador->getTablero()[(int) this->coord_x][(int) this->coord_z]);
        if (est->getDestructible()) {
            glBindTexture(GL_TEXTURE_2D, controlador->getTextura1());
        }
        else {
            glBindTexture(GL_TEXTURE_2D, controlador->getTextura2());
        }

    }

    GLfloat xReal = (this->coord_x - 14.5f) * global->largoEstructura;
    GLfloat zReal = (this->coord_z - 5.5f) * global->largoEstructura;

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    // Cara frontal (z = 1/2)
    if (textura) {
        glTexCoord2f(0, 0);
    }
    glVertex3f(xReal, 0, zReal + global->largoEstructura);
    if (textura) {
        glTexCoord2f(0, 1);
    }
    glVertex3f(xReal + global->largoEstructura, 0, zReal + global->largoEstructura);
    if (textura) {
        glTexCoord2f(1, 1);
    }
    glVertex3f(xReal + global->largoEstructura, global->largoEstructura, zReal + global->largoEstructura);
    if (textura) {
        glTexCoord2f(1, 0);
    }
    glVertex3f(xReal, global->largoEstructura, zReal + global->largoEstructura);

    // Cara posterior (z = -1/2)
    glColor3f(1.0, 1.0, 1.0);
    if (textura) {
        glTexCoord2f(0, 0);
    }
    glVertex3f(xReal, 0, zReal);
    if (textura) {
        glTexCoord2f(0, 1);
    }
    glVertex3f(xReal + global->largoEstructura, 0, zReal);
    if (textura) {
        glTexCoord2f(1, 1);
    }
    glVertex3f(xReal + global->largoEstructura, global->largoEstructura, zReal);
    if (textura) {
        glTexCoord2f(1, 0);
    }
    glVertex3f(xReal, global->largoEstructura, zReal);

    // Cara superior (y = 1/2)
    glColor3f(1.0, 1.0, 1.0);
    if (textura) {
        glTexCoord2f(0, 0);
    }
    glVertex3f(xReal, global->largoEstructura, zReal);
    if (textura) {
        glTexCoord2f(0, 1);
    }
    glVertex3f(xReal + global->largoEstructura, global->largoEstructura, zReal);
    if (textura) {
        glTexCoord2f(1, 1);
    }
    glVertex3f(xReal + global->largoEstructura, global->largoEstructura, zReal + global->largoEstructura);
    if (textura) {
        glTexCoord2f(1, 0);
    }
    glVertex3f(xReal, global->largoEstructura, zReal + global->largoEstructura);

    // Cara inferior (y = -1/2)
    glColor3f(1.0, 1.0, 1.0);
    if (textura) {
        glTexCoord2f(0, 0);
    }
    glVertex3f(xReal, 0, zReal);
    if (textura) {
        glTexCoord2f(0, 1);
    }
    glVertex3f(xReal + global->largoEstructura, 0, zReal);
    if (textura) {
        glTexCoord2f(1, 1);
    }
    glVertex3f(xReal + global->largoEstructura, 0, zReal + global->largoEstructura);
    if (textura) {
        glTexCoord2f(1, 0);
    }
    glVertex3f(xReal, 0, zReal + global->largoEstructura);

    // Cara izquierda (x = -1/2)
    glColor3f(1.0, 1.0, 1.0);
    if (textura) {
        glTexCoord2f(0, 0);
    }
    glVertex3f(xReal, 0, zReal);
    if (textura) {
        glTexCoord2f(0, 1);
    }
    glVertex3f(xReal, 0, zReal + global->largoEstructura);
    if (textura) {
        glTexCoord2f(1, 1);
    }
    glVertex3f(xReal, global->largoEstructura, zReal + global->largoEstructura);
    if (textura) {
        glTexCoord2f(1, 0);
    }
    glVertex3f(xReal, global->largoEstructura, zReal);

    // Cara derecha (x = 1/2)
    glColor3f(1.0, 1.0, 1.0);
    if (textura) {
        glTexCoord2f(0, 0);
    }
    glVertex3f(xReal + global->largoEstructura, 0, zReal);
    if (textura) {
        glTexCoord2f(0, 1);
    }
    glVertex3f(xReal + global->largoEstructura, 0, zReal + global->largoEstructura);
    if (textura) {
        glTexCoord2f(1, 1);
    }
    glVertex3f(xReal + global->largoEstructura, global->largoEstructura, zReal + global->largoEstructura);
    if (textura) {
        glTexCoord2f(1, 0);
    }
    glVertex3f(xReal + global->largoEstructura, global->largoEstructura, zReal);
    glEnd();
}

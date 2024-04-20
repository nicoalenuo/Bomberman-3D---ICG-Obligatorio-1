#include "../lib/objeto.h"


posicion objeto::getPosicion() {return pos;}

tamanio objeto::getTamanio() {return tam;}

void objeto::setPosicionX(GLfloat x) {this->pos.x = x;}

void objeto::setPosicionY(GLfloat y) {this->pos.y = y;}

void objeto::setPosicionZ(GLfloat z) {this->pos.z = z;}

void objeto::setTamanioX(GLfloat x) {this->tam.x = x;}

void objeto::setTamanioY(GLfloat y) {this->tam.y = y;}

void objeto::setTamanioZ(GLfloat z) {this->tam.z = z;}
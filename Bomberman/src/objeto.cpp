#include "../lib/objeto.h"


posicion objeto::getPosicion() { return pos; }

tamanio objeto::getTamanio() { return tam; }

void objeto::setPosicionX(GLfloat x) { pos.x = x; }

void objeto::setPosicionY(GLfloat y) { pos.y = y; }

void objeto::setPosicionZ(GLfloat z) { pos.z = z; }

void objeto::setTamanioX(GLfloat x)  { tam.x = x; }

void objeto::setTamanioY(GLfloat y)  { tam.y = y; }

void objeto::setTamanioZ(GLfloat z)  { tam.z = z; }
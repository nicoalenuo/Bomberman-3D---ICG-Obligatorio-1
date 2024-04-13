#pragma once

#include "objeto.h"
#include "bonificador.h"

class estructura : public objeto {
private:
	bool destructible; //true si se puede destruir, false si es indestructible
	bonificador* powerUp; // [ (powerUp != nullptr) -> destructible ] /\ [ not(destructible -> (powerUp != nullptr)) ]
public:
	estructura(int x, int z, bool dest);
	bool getDestructible();
	void setDestructible(bool dest);
	bonificador* getPowerUp();
	void setPowerUp(bonificador* power);
};


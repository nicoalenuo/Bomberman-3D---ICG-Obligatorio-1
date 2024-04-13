#pragma once

class objeto { //abstracta
protected:
	float coord_x;
	float coord_z;
public:
	virtual float getCoordX();
	virtual float getCoordZ();
	virtual void setCoordX(float x);
	virtual void setCoordZ(float z);
};


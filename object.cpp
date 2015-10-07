//object.cpp

#include "object.h"

cObject::cObject(int nx, int ny, int nw, int nh, sRect &ncolBox, float nxVel, float nyVel, eObjType ntype){
	x = nx;
	y = ny;
	w = nw;
	h = nh;
	colBox = ncolBox;
	xVel = nxVel;
	yVel = nyVel;
	type = ntype;
}

cObject::~cObject(){
}

float cObject::getX(){
	return x;
}

float cObject::getY(){
	return y;
}

int cObject::getW(){
	return w;
}

int cObject::getH(){
	return h;
}

float cObject::getXVel(){
	return xVel;
}

float cObject::getYVel(){
	return yVel;
}

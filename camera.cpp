//camera.cpp

#include "camera.h"
#include <iostream>
using namespace std;

cCamera::cCamera(int xPos, int yPos){
	x = xPos;
	y = yPos;
	xVel = 0;
	yVel = 0;
	focX = xPos;
	focY = yPos;
}

cCamera::~cCamera(){
}

void cCamera::focus(int xPos, int yPos){
	focX = xPos;
	focY = yPos;
}

void cCamera::think(){
	xVel = ((float)focX - x)*kCamAcc;
	yVel = ((float)focY - y)*kCamAcc;
	x += xVel;
	y += yVel;
}

int cCamera::getX(){
	return (int)x;
}

int cCamera::getY(){
	return (int)y;
}

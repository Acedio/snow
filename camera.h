//camera.h

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "graphics.h"

const float kCamAcc = .05;

class cCamera{
public:
	cCamera(int xPos, int yPos);
	~cCamera();
	void focus(int xPos, int yPos);
	void think();
	int getX();
	int getY();
private:
	int focX, focY;
	float x, y;
	float xVel, yVel;
};

#endif

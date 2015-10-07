//object.h
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include "tileMap.h"
#include "graphics.h"
#include "camera.h"

class cObjectManager;

enum eObjType {O_PLAYER};

enum eObjState {S_OK, S_REMOVE};

class cObject{
public:
	cObject(int nx, int ny, int nw, int nh, sRect &ncolBox, float nxVel, float nyVel, eObjType ntype);
	virtual ~cObject();
	virtual eObjState think() = 0; // pure virtual
	virtual void draw(cDisplay* display, cSurfaceManager* surfaceManager, cAnimationManager* animationManager, cCamera* camera) = 0;
	virtual void mapCollide(cTileMap* tileMap) = 0;
	virtual void collide(cObject *object) = 0;
	float getX();
	float getY();
	int getW();
	int getH();
	float getXVel();
	float getYVel();
protected:
	float x,y; // pixmap upper left corner
	int w,h; // width + height of pixmap
	sRect colBox; // collision rectangle
	float xVel, yVel;
	eObjType type;
	bool inair; // should these be part of cObject?
	float xFriction, yFriction;
private:
	friend class cObjectManager;
};

#endif

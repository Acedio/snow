//objectManager.h

#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <vector>
#include <cmath>
#include "tileMap.h"
#include "object.h"
#include "graphics.h"
#include "camera.h"
using namespace std;

class cObjectManager{
public:
	cObjectManager();
	~cObjectManager();
	void think(cTileMap* tileMap);
	void draw(cDisplay* display, cSurfaceManager* surfaceManager, cAnimationManager* animationManager, cCamera* camera);
	void add(cObject* object);
private:
	vector<cObject*> objects;
	void collide(cObject* object, cTileMap* tileMap);
};

#endif

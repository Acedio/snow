//game.h

#include "graphics.h"
#include "tileMap.h"
#include "object.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "timer.h"
#include "objectManager.h"
#include <iostream>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#define TIXML_USE_STL

const int kScreenWidth = 320;
const int kScreenHeight = 240;

const int kThinkPerSec = 100;

class cGame{
public:
	cGame();
	~cGame();
	void run();
private:
	cDisplay* display;
	cSurfaceManager* surfaceManager;
	cAnimationManager* animationManager;
	cTileMap* tileMap;
	cInput* input;
	cCamera* camera;
	cPlayer* player;
	cObjectManager* objectManager;
	cTimer* timer;
};

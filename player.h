//player.h

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <map>
#include "input.h"
#include "object.h"

const float kPlayerAcc = .05;
const float kPlayerMaxVel = 1.0;
const float kPlayerDec = .03;
const float kJumpVel = 1.2;
const float kJumpAcc = .015;
const int kMaxJumpFrames = 40;

enum ePlayerAnimState {P_WALK, P_JUMP, P_STAND};

struct sPlayerAnimations{
	int runLeft, runRight;
	int walkLeft, walkRight;
	int jumpLeft, jumpRight;
	int standLeft, standRight;
};

class cPlayer: public cObject{
public:
	cPlayer(int nx, int ny, int nw, int nh, sRect &ncolBox, float nxVel, float nyVel, sPlayerAnimations animations);
	void processInput(cInput* input);
	eObjState think();
	//void draw(cDisplay* display, cSurfaceManager* surfaceManager, cCamera* camera);
	void draw(cDisplay* display, cSurfaceManager* surfaceManager, cAnimationManager* animationManager, cCamera* camera);
	void collide(cObject* object);
	void mapCollide(cTileMap* tileMap);
private:
	sPlayerAnimations playerAnimations;
	int currentAnimation;
	int jumpFrames;
	int noJump;
	bool facingRight;
};

#endif

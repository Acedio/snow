//player.cpp

#include "player.h"
#include <iostream>
using namespace std;

cPlayer::cPlayer(int nx, int ny, int nw, int nh, sRect &ncolBox, float nxVel, float nyVel, sPlayerAnimations animations): cObject(nx,ny,nw,nh,ncolBox,nxVel,nyVel,O_PLAYER){
	playerAnimations = animations;
	currentAnimation = playerAnimations.walkRight;
	xFriction = .3;
	//yFriction = 1;
}

eObjState cPlayer::think(){
	//x += xVel;
	//y += yVel;
	return S_OK;
}

/*void cPlayer::draw(cDisplay* display, cSurfaceManager* surfaceManager, cCamera* camera){
	surfaceManager->drawSurface(display,gfx,(int)(display->getW()/2+x-camera->getX()),(int)(display->getH()/2+y-camera->getY()));
}*/

void cPlayer::draw(cDisplay* display, cSurfaceManager* surfaceManager, cAnimationManager* animationManager, cCamera* camera){
	animationManager->drawAnimation(currentAnimation, surfaceManager, display, (int)(display->getW()/2+x-camera->getX()),(int)(display->getH()/2+y-camera->getY()));
}

void cPlayer::collide(cObject* object){
}

void cPlayer::mapCollide(cTileMap* tileMap){
	int cx,cy;
	/*int divx = (int)ceil(w/kTileSize) + 1, divy = (int)ceil(h/kTileSize) + 1;
	for(cx = 0; cx <= w - 1; cx += (w-1)/divx){
		if(tileMap->tileType((int)(x + cx), (int)(y + yVel)) == T_SOLID){
			yVel = (int)(((y + h + yVel)/kTileSize))*kTileSize - y;
		}
		if(tileMap->tileType((int)(x + cx), (int)(y + h + yVel)) == T_SOLID){
			yVel = (int)(((y + yVel)/kTileSize))*kTileSize - y;
			inair = false;
		} else {
			inair = true;
		}
	}
	y += yVel;
	for(cy = 0; cy <= h - 1; cy += (h-1)/divy){
		if(tileMap->tileType((int)(x + xVel), (int)(y + cy)) == T_SOLID){
			xVel = (int)(((x + w + xVel)/kTileSize))*kTileSize - x;
		}
		if(tileMap->tileType((int)(x + w + xVel), (int)(y + cy)) == T_SOLID){
			xVel = (int)(((x + xVel)/kTileSize))*kTileSize - x;
		}
	}
	x += xVel;*/

	// left and right
	x += xVel;
	for(cy = colBox.y; cy < colBox.h; cy += kTileSize){
		// left
		if(tileMap->tileType((int)(x + colBox.x),(int)(y + colBox.y + cy)) == T_SOLID){
			x += kTileSize - (int)(x + colBox.x)%kTileSize;
			xVel = 0;
		}
		// right
		if(tileMap->tileType((int)(x + colBox.x + colBox.w),(int)(y + colBox.y + cy)) == T_SOLID){
			x -= (int)(x + colBox.x + colBox.w)%kTileSize;
			xVel = 0;
		}
	}
	// left bottom
	if(tileMap->tileType((int)(x + colBox.x),(int)(y + colBox.y + colBox.h - 1)) == T_SOLID){
		x += kTileSize - (int)(x + colBox.x)%kTileSize;
		xVel = 0;
	}
	// right bottom
	if(tileMap->tileType((int)(x + colBox.x + colBox.w),(int)(y + colBox.y + colBox.h - 1)) == T_SOLID){
		x -= (int)(x + colBox.x + colBox.w)%kTileSize;
		xVel = 0;
	}

	// top and bottom
	yVel += .032;
	y += yVel;
	inair = true;
	for(cx = colBox.x; cx < colBox.w; cx += kTileSize){
		// top
		if(tileMap->tileType((int)(x + colBox.x + cx), (int)(y + colBox.y)) == T_SOLID){
			y += kTileSize - (int)(y + colBox.y)%kTileSize;
			yVel = 0;
		}
		// bottom
		if(tileMap->tileType((int)(x + colBox.x + cx), (int)(y + colBox.y + colBox.h)) == T_SOLID){
			y -= (int)(y + colBox.y + colBox.h)%kTileSize;
			yVel = 1; // so we hit the ground again next turn
			inair = false;
		}
	}
	// bottom right
	if(tileMap->tileType((int)(x + colBox.x + colBox.w - 1), (int)(y + colBox.y + colBox.h)) == T_SOLID){
		y -= (int)(y + colBox.y + colBox.h)%kTileSize;
		yVel = 1;
		inair = false;
	}
	// top right
	if(tileMap->tileType((int)(x + colBox.x + colBox.w - 1), (int)(y + colBox.y)) == T_SOLID){
		y += kTileSize - (int)(y + colBox.y)%kTileSize;
		yVel = 0;
	}
	if(inair){
		noJump = true;
	}
}

void cPlayer::processInput(cInput* input){
	/*xVel = 0;
	if(input->isKeyDown(K_UP)){
		yVel = -kPlayerMaxVel;
	}
	if(input->isKeyDown(K_DOWN)){
		yVel = kPlayerMaxVel;
	}
	if(input->isKeyDown(K_LEFT)){
		xVel = -kPlayerMaxVel;
	}
	if(input->isKeyDown(K_RIGHT)){
		xVel = kPlayerMaxVel;
	}*/
	if(input->isKeyDown(K_UP)){
		if(!inair && !noJump){
			yVel = -kJumpVel; // inital jump velocity
			inair = true;
			jumpFrames = 0;
			noJump = true;
		} else if (jumpFrames < kMaxJumpFrames && yVel < 0) {
			yVel -= kJumpAcc; // jump acceleration (you can fudge the jump a bit.)
			jumpFrames++;
		}
	} else {
		if(!inair){ // you must be on the ground and have the up key released to jump again
			noJump = false;
		}
		jumpFrames = kMaxJumpFrames;
	}
	if(input->isKeyDown(K_DOWN)){
	}
	if(!inair){
		currentAnimation = (facingRight?playerAnimations.standRight:playerAnimations.standLeft);
	}
	if(input->isKeyDown(K_LEFT) || input->isKeyDown(K_RIGHT)){
		if(input->isKeyDown(K_LEFT)){
			currentAnimation = playerAnimations.runLeft;
			xVel -= kPlayerAcc;
			if(xVel < -kPlayerMaxVel){
				xVel = -kPlayerMaxVel;
			}
			facingRight = false;
		}
		if(input->isKeyDown(K_RIGHT)){
			currentAnimation = playerAnimations.runRight;
			xVel += kPlayerAcc;
			if(xVel > kPlayerMaxVel){
				xVel = kPlayerMaxVel;
			}
			facingRight = true;
		}
	} else {
		xVel = 0;
	}
	if(inair){
		currentAnimation = (facingRight?playerAnimations.jumpRight:playerAnimations.jumpLeft);
	}
}

//objectManager.cpp

#include "objectManager.h"
#include <cmath>
#include <iostream>

cObjectManager::cObjectManager(){
}

cObjectManager::~cObjectManager(){
	while(!objects.empty()){
		delete objects.back();
		objects.pop_back();
	}
}

void cObjectManager::think(cTileMap* tileMap){
	vector<cObject*>::iterator i, j;
	for(i = objects.begin(); i != objects.end(); i++){
		//(*i)->yVel += .1;
		if((*i)->think() == S_REMOVE){
			vector<cObject*>::iterator temp = i; // need a copy so we don't invalidate i
			i--; // move i back from the removee
			objects.erase(temp); // erase it!
		}
		collide(*i,tileMap);
	}
}

void cObjectManager::draw(cDisplay* display, cSurfaceManager* surfaceManager, cAnimationManager* animationManager, cCamera* camera){
	vector<cObject*>::iterator i;
	for(i = objects.begin(); i != objects.end(); i++){
		(*i)->draw(display, surfaceManager, animationManager, camera);
	}
}

void cObjectManager::add(cObject* object){
	objects.push_back(object);
}

void cObjectManager::collide(cObject* object, cTileMap* tileMap){
	object->mapCollide(tileMap);
}

//input.cpp

#include "input.h"
#include <iostream>
using namespace std;

cInput::cInput(){
	// VIDEO MUST BE INITIALIZED PREVIOUS TO INPUT
}

cInput::~cInput(){
}

bool cInput::quitEvent(){
	while(SDL_PollEvent(&e)){
		if(e.type == SDL_QUIT){
			return true;
		} else if(e.type == SDL_KEYUP) {
			if(e.key.keysym.sym == SDLK_ESCAPE){
				return true;
			}
		}
	}
	return false;
}

void cInput::update(){
	keystates = SDL_GetKeyState(NULL);
}

bool cInput::isKeyDown(eKeys key){
	return keystates[key];
}

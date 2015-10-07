//timer.cpp

#include "timer.h"

cTimer::cTimer(){
	started = false;
	paused = false;
	startTicks = 0;
	pausedTicks = 0;
}

cTimer::~cTimer(){
}

void cTimer::start(){
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
}

void cTimer::stop(){
	started = false;
	paused = false;
}

void cTimer::pause(){
	if(started && !paused){
		paused = true;

		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void cTimer::unpause(){
	if(paused){
		paused = false;

		startTicks = SDL_GetTicks() - pausedTicks;

		pausedTicks = 0;
	}
}

int cTimer::getTicks(){
	if(started){
		if(paused){
			return pausedTicks;
		} else {
			return SDL_GetTicks() - startTicks;
		}
	}
	return 0;
}

bool cTimer::isStarted(){
	return started;
}

bool cTimer::isPaused(){
	return paused;
}

void cTimer::delay(int time){
	SDL_Delay(time);
}

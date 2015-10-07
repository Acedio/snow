//timer.h

#ifndef _TIMER_H_
#define _TIMER_H_

#include <SDL/SDL.h>

class cTimer{
public:
	cTimer();
	~cTimer();

	void start();
	void stop();

	void pause();
	void unpause();
	
	int getTicks();

	bool isStarted();
	bool isPaused();

	void delay(int time);
private:
	bool started;
	bool paused;

	int startTicks;
	int pausedTicks;
};

#endif

//input.h

#ifndef _INPUT_H_
#define _INPUT_H_

#include <SDL/SDL.h>

enum eEventType {E_NONE,E_QUIT};
enum eKeys {K_UP = SDLK_UP,
K_DOWN = SDLK_DOWN,
K_LEFT = SDLK_LEFT,
K_RIGHT = SDLK_RIGHT};

class cInput{
public:
	cInput();
	~cInput();
	bool quitEvent();
	void update();
	bool isKeyDown(eKeys key);
private:
	SDL_Event e;
	Uint8* keystates;
};

#endif

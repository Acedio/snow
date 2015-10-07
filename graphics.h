// graphics.h
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <map>
#include <vector>

struct sRect{
	int x, y, w, h;
};

struct sSurface{
	SDL_Surface* surface;
	std::string filename;
	int width;
	int height;
};

struct sSurfaceSection{
	int surfaceId;
	sRect section;
	int width;
	int height;
	friend bool operator==(const sSurfaceSection& x, const sSurfaceSection& y);
};

class cDisplay{
public:
	cDisplay(int w, int h, int bpp);
	~cDisplay();
	void blit(sSurface* src, sRect* srcRect, int x, int y);
	void flip();
	int getW();
	int getH();
	void clear();
private:
	SDL_Surface* screen;
};

class cSurfaceManager{
public:
	cSurfaceManager();
	~cSurfaceManager();

	int loadSurface(std::string filename);
	
	int createSurfaceSection(int surfaceId, sRect section);
	
	void removeSurface(int surfaceId);
	void removeSurfaceSection(int sectionId);

	void drawSurface(cDisplay* display, int surfaceId, int x, int y);
	void drawSurfaceSection(cDisplay* display, int sectionId, int x, int y);

	void removeAllSurfaces();
	void removeAllSurfaceSections();
private:
	std::map<int, sSurface> surfaces;
	std::map<int, sSurfaceSection> sections;
};

class cAnimation{
public:
	cAnimation();
	~cAnimation();

	void update();
	void pause();
	void resume();
	void reset();
	void jumpToFrame(int frame);

	void addFrame(int surfaceSection, int duration);
	int setFrameSurfaceSection(int position, int surfaceSection);
	int setFrameDuration(int position, int duration);
	void draw(cSurfaceManager* surfaceManager, cDisplay* display, int x, int y);
private:
	std::vector<int> frames;
	std::vector<int> durations;
	int currentFrameTicks;
	int currentFrame;
	bool paused;
};

class cAnimationManager{
public:
	cAnimationManager();
	~cAnimationManager();

	int createAnimation(std::vector<int> frames, std::vector<int> durations);
	int createAnimation(std::vector<int> frames, int duration);
	int createAnimationFromSurface(int surfaceId, sRect location, int xParts, int yParts, std::vector<int> frameLocations, std::vector<int> frameDurations, int fps);

	void remove(int animation);
	void removeAll();

	void pause(int animation);
	void pauseAll();

	void update(int animation);
	void updateAll();

	void resume(int animation);
	void resumeAll();

	void reset(int animation);
	void resetAll();

	void jumpToFrame(int animation, int frame);

	void drawAnimation(int animation, cSurfaceManager* surfaceManager, cDisplay* display, int x, int y);
private:
	std::map<int,cAnimation> animations;
};

#endif

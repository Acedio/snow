//graphics.cpp
#include "graphics.h"
#include <iostream>
using namespace std;

bool operator==(const sSurfaceSection& x, const sSurfaceSection& y){
	if(x.surfaceId == y.surfaceId && x.section.x == y.section.x && x.section.y == y.section.y && x.section.w == y.section.w && x.section.h == y.section.h && x.width == y.width && x.height == y.height){
		return 1;
	}
	//cout << x.surfaceId << " " << y.surfaceId << " " << x.section.x << " " << y.section.y << " " << x.section.y << " " << y.section.y << " " << x.section.w << " " << y.section.w << " " << x.section.h << " " << y.section.h << " " << x.width << " " << y.width << " " << x.height << " " << y.height << endl;
	return 0;
}

cSurfaceManager::cSurfaceManager(){
}

cSurfaceManager::~cSurfaceManager(){
	cout << surfaces.size() << " surfaces" << endl;
	cout << sections.size() << " sections" << endl;
	removeAllSurfaces();
	removeAllSurfaceSections();
}

int cSurfaceManager::loadSurface(std::string filename){
	sSurface temp;
	SDL_Surface* unoptimized;
	temp.filename = filename;
	unoptimized = IMG_Load(filename.c_str());
	if(!unoptimized){
		cout << filename << ": " << IMG_GetError() << endl;
	} else {
		temp.surface = SDL_DisplayFormat(unoptimized);
		SDL_SetColorKey(temp.surface,SDL_SRCCOLORKEY,SDL_MapRGB(temp.surface->format,0xFF,0,0xFF));
		temp.width = temp.surface->clip_rect.w;
		temp.height = temp.surface->clip_rect.h;
		return surfaces.insert(pair<int,sSurface>(surfaces.end()->first+1,temp)).first->first; // return it's int key
	}
	return 0;
}

int cSurfaceManager::createSurfaceSection(int surfaceId, sRect section){
	sSurfaceSection temp;
	temp.surfaceId = surfaceId;
	temp.section = section;
	temp.width = section.w;
	temp.height = section.h;
	if(!sections.empty()){
		std::map<int,sSurfaceSection>::iterator i;
		for(i = sections.begin(); i != sections.end(); i++){
			if(temp == i->second){
				return i->first;
			}
		}
	}
	sections.insert(pair<int,sSurfaceSection>(sections.size(),temp));
	return sections.size()-1;
}

void cSurfaceManager::removeSurface(int surfaceId){
	SDL_FreeSurface(surfaces[surfaceId].surface);
	surfaces.erase(surfaceId);
}

void cSurfaceManager::removeSurfaceSection(int sectionId){
	sections.erase(sectionId);
}

void cSurfaceManager::drawSurface(cDisplay* display, int surfaceId, int x, int y){
	sRect temp;
	temp.x = temp.y = 0;
	display->blit(&surfaces.at(surfaceId), NULL, x, y);
}

void cSurfaceManager::drawSurfaceSection(cDisplay* display, int sectionId, int x, int y){
	display->blit(&surfaces[sections[sectionId].surfaceId], &sections[sectionId].section, x, y);
}

void cSurfaceManager::removeAllSurfaces(){
	std::map<int, sSurface>::iterator i;
	for(i = surfaces.begin(); i != surfaces.end(); i++){
		SDL_FreeSurface(i->second.surface);
	}
	surfaces.clear();
}

void cSurfaceManager::removeAllSurfaceSections(){
	sections.clear();
}


cDisplay::cDisplay(int w, int h, int bpp){
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(w,h,bpp,SDL_SWSURFACE|SDL_FULLSCREEN);
}

cDisplay::~cDisplay(){
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	screen = NULL;
}

void cDisplay::blit(sSurface* src, sRect* srcRect, int x, int y){
	SDL_Rect dstTemp, srcTemp;
	dstTemp.x = x;
	dstTemp.y = y;
	if(srcRect != NULL){
		srcTemp.x = srcRect->x;
		srcTemp.y = srcRect->y;
		srcTemp.w = srcRect->w;
		srcTemp.h = srcRect->h;
		SDL_BlitSurface(src->surface, &srcTemp, screen, &dstTemp);
	} else {
		SDL_BlitSurface(src->surface, NULL, screen, &dstTemp);
	}
}

void cDisplay::flip(){
	SDL_Flip(screen);
}

int cDisplay::getW(){
	return screen->w;
}

int cDisplay::getH(){
	return screen->h;
}

void cDisplay::clear(){
	SDL_FillRect(screen, NULL, 0);
}

cAnimation::cAnimation(){
	currentFrame = 0;
	currentFrameTicks = 0;
	paused = false;
}

cAnimation::~cAnimation(){
}

void cAnimation::update(){
	if(!paused){
		if(++currentFrameTicks >= durations[currentFrame]){
			currentFrameTicks = 0;
			if(++currentFrame >= (int)frames.size()){
				currentFrame = 0;
			}
		}
	}
}

void cAnimation::pause(){
	paused = true;
}

void cAnimation::resume(){
	paused = false;
}

void cAnimation::reset(){
	paused = false;
	currentFrame = 0;
	currentFrameTicks = 0;
}

void cAnimation::jumpToFrame(int frame){
	currentFrame = frame;
	currentFrameTicks = 0;
}

void cAnimation::addFrame(int surfaceSection, int duration){
	frames.push_back(surfaceSection);
	durations.push_back(duration);
}

int cAnimation::setFrameSurfaceSection(int position, int surfaceSection){
	if(position >= (int)frames.size()){
		return -1;
	}
	frames[position] = surfaceSection;
	return 0;
}

int cAnimation::setFrameDuration(int position, int duration){
	if(position >= (int)frames.size()){
		return -1;
	}
	durations[position] = duration;
	return 0;
}

void cAnimation::draw(cSurfaceManager* surfaceManager, cDisplay* display, int x, int y){
	int sectionToDraw = frames.at(currentFrame);
	surfaceManager->drawSurfaceSection(display, sectionToDraw, x, y);
}

cAnimationManager::cAnimationManager(){
}

cAnimationManager::~cAnimationManager(){
}

int cAnimationManager::createAnimation(std::vector<int> frames, std::vector<int> durations){
	if(frames.size() != durations.size()){
		return -1; // we need a frame for every duration
	}
	cAnimation temp;
	int i;
	for(i = 0; i < (int)frames.size(); i++){
		temp.addFrame(frames.at(i),durations.at(i));
	}
	return animations.insert(pair<int,cAnimation>(animations.end()->first + 1, temp)).first->first; // return animation key
}

int cAnimationManager::createAnimation(std::vector<int> frames, int duration){
	cAnimation temp;
	int i;
	for(i = 0; i < (int)frames.size(); i++){
		temp.addFrame(frames.at(i),duration);
	}
	return animations.insert(pair<int,cAnimation>(animations.end()->first + 1, temp)).first->first; // return animation key
}

void cAnimationManager::remove(int animation){
	animations.erase(animation);
}

void cAnimationManager::removeAll(){
	animations.clear();
}

void cAnimationManager::pause(int animation){
	animations[animation].pause();
}

void cAnimationManager::pauseAll(){
	std::map<int,cAnimation>::iterator i;
	for(i = animations.begin(); i != animations.end(); i++){
		i->second.pause();
	}
}

void cAnimationManager::update(int animation){
	animations[animation].update();
}

void cAnimationManager::updateAll(){
	std::map<int,cAnimation>::iterator i;
	for(i = animations.begin(); i != animations.end(); i++){
		i->second.update();
	}
}

void cAnimationManager::resume(int animation){
	animations[animation].resume();
}

void cAnimationManager::resumeAll(){
	std::map<int,cAnimation>::iterator i;
	for(i = animations.begin(); i != animations.end(); i++){
		i->second.resume();
	}
}

void cAnimationManager::reset(int animation){
	animations[animation].reset();
}

void cAnimationManager::resetAll(){
	std::map<int,cAnimation>::iterator i;
	for(i = animations.begin(); i != animations.end(); i++){
		i->second.reset();
	}
}

void cAnimationManager::jumpToFrame(int animation, int frame){
	animations[animation].jumpToFrame(frame);
}

void cAnimationManager::drawAnimation(int animation, cSurfaceManager* surfaceManager, cDisplay* display, int x, int y){
	animations[animation].draw(surfaceManager, display, x, y);
}

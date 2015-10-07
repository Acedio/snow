//game.cpp

#include "game.h"
#include "globals.h"
#include <vector>

cGame::cGame(){
	int width = 0, height = 0, xStart = 0, yStart = 0, undefinedTile = 0;
	string tiledata, coldata, tileset;

	SDL_Init(0);
	display = new cDisplay(kScreenWidth,kScreenHeight,32);
	surfaceManager = new cSurfaceManager();
	animationManager = new cAnimationManager();

	TiXmlDocument doc("level0.xml");
	doc.LoadFile();
	TiXmlHandle handle(&doc);

	TiXmlElement* elem = handle.FirstChild("level").FirstChild("map").FirstChild("width").ToElement();
	if(!elem){
		cout << "Misformed width in level file" << endl;
	} else {
		width = strToInt(elem->GetText());
	}

	elem = handle.FirstChild("level").FirstChild("map").FirstChild("height").ToElement();
	if(!elem){
		cout << "Misformed height in level file" << endl;
	} else {
		height = strToInt(elem->GetText());
	}

	elem = handle.FirstChild("level").FirstChild("map").FirstChild("tiledata").ToElement();
	if(!elem){
		cout << "Misformed tiledata in level file" << endl;
	} else {
		tiledata = elem->GetText();
		elem->Attribute("undefined",&undefinedTile);
	}

	elem = handle.FirstChild("level").FirstChild("map").FirstChild("coldata").ToElement();
	if(!elem){
		cout << "Misformed coldata in level file" << endl;
	} else {
		coldata = elem->GetText();
	}

	elem = handle.FirstChild("level").FirstChild("map").FirstChild("tileset").ToElement();
	if(!elem){
		cout << "Misformed tileset in level file" << endl;
	} else {
		tileset = elem->GetText();
	}

	elem = handle.FirstChild("level").FirstChild("startpos").ToElement();
	if(!elem){
		cout << "No startpos in level file" << endl;
	} else {
		elem->Attribute("x",&xStart);
		elem->Attribute("y",&yStart);
	}

	char temp[20];
	strcpy(temp, tileset.c_str());

	tileMap = new cTileMap(width, height, tiledata, coldata, surfaceManager, surfaceManager->loadSurface(temp), undefinedTile);

	input = new cInput();

	// lets create us a phil! first the gfx
	sPlayerAnimations philAnimations;
	int philGfx = surfaceManager->loadSurface("phil.png");

	// RIGHT
	std::vector<int> frames;
	sRect philRect = {0,0,16,16};
	// stand
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philAnimations.standRight = animationManager->createAnimation(frames, 100); // we'll cheat and just use the first frame for standing

	// walk
	philRect.x = 16; // move to left stride
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philRect.x = 0; // move back to original
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philRect.x = 32; // move to right stride
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philAnimations.walkRight = animationManager->createAnimation(frames, 10); // generic duration of 10 ticks per frame

	// run
	frames.clear();
	philRect.x = 48;
	philRect.y = 48;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect)); // hold for two
	philRect.x = 32;
	philRect.y = 0;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philRect.x = 16;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philRect.x = 32;
	philRect.y = 48;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philRect.x = 16;
	philRect.y = 0;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philRect.x = 32;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philAnimations.runRight = animationManager->createAnimation(frames, 7);

	// jump
	frames.clear();
	philRect.x = 48;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philAnimations.jumpRight = animationManager->createAnimation(frames, 10); // jumping yay
	
	// LEFT
	frames.clear();
	philRect.y = 16;
	philRect.x = 0;
	// stand
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philAnimations.standLeft = animationManager->createAnimation(frames, 100); // we'll cheat and just use the first frame for standing

	// walk
	philRect.x = 16; // move to left stride
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philRect.x = 0; // move back to original
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philRect.x = 32; // move to right stride
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philAnimations.walkLeft = animationManager->createAnimation(frames, 10); // generic duration of 10 ticks per frame

	// run
	frames.clear();
	philRect.x = 48;
	philRect.y = 64;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect)); // hold for two
	philRect.x = 32;
	philRect.y = 16;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philRect.x = 16;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philRect.x = 32;
	philRect.y = 64;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philRect.x = 16;
	philRect.y = 16;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philRect.x = 32;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philAnimations.runLeft = animationManager->createAnimation(frames, 7);

	// jump
	frames.clear();
	philRect.x = 48;
	frames.push_back(surfaceManager->createSurfaceSection(philGfx, philRect));
	philAnimations.jumpLeft = animationManager->createAnimation(frames, 10); // jumping yay

	sRect tempRect = {0,1,14,15}; // collision box data
	player = new cPlayer(xStart*16,yStart*16,16,16,tempRect,0,0,philAnimations);
	objectManager = new cObjectManager();
	objectManager->add(player);
	camera = new cCamera(160,120);
	timer = new cTimer();
}

cGame::~cGame(){
	delete display;
	delete tileMap;
	delete input;
	delete camera;
	delete timer;
	SDL_Quit();
}

void cGame::run(){
	timer->start();
	int lastTicks = timer->getTicks();
	int frames = 0;
	while(!input->quitEvent()){
		int ticks = timer->getTicks();
		input->update();
		if(lastTicks < ticks){
			while(lastTicks < ticks){
				player->processInput(input);
				objectManager->think(tileMap);
				animationManager->updateAll();
				camera->focus((int)player->getX(),(int)player->getY());
				camera->think();
				lastTicks += 1000/kThinkPerSec;
			}
			display->clear();
			tileMap->draw(display, surfaceManager, camera);
			objectManager->draw(display, surfaceManager, animationManager, camera);
			display->flip();
			frames++;
			// display fps
			//cout << (1000*frames)/(timer->getTicks()) << endl;
		} else {
			timer->delay(1);
		}
	}
	delete surfaceManager;
}

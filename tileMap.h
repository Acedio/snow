//tileMap.h
#ifndef _TILEMAP_H_
#define _TILEMAP_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "graphics.h"
#include "camera.h"
#include "globals.h"

using namespace std;

const int kTileSize = 16;

enum eTileType {T_PASSABLE,T_SOLID,T_SLOPE_UP,T_SLOPE_DOWN};

typedef struct{
	eTileType type;
	int gfx;
} sTile;

class cTileMap{
public:
	cTileMap(int width, int height, string tiledata, string coldata, cSurfaceManager* surfaceManager, int set, int undefined);
	void draw(cDisplay* display, cSurfaceManager* surfaceManager, cCamera* camera);
	eTileType tileType(int x, int y); // x and y are real coords, not just tile coordinates
	~cTileMap();
private:
	int w, h;
	int undefinedTile;
	sTile** tiles;
};
#endif

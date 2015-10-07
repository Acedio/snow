//tileMap.cpp
#include "tileMap.h"
using namespace std;

cTileMap::cTileMap(int width, int height, string tiledata, string coldata, cSurfaceManager* surfaceManager, int set, int undefined){
	int x,y,strpos = 0, slen = 0;

	//cout << tiledata << endl << endl << coldata << endl << endl;

	w = width;
	h = height;

	sRect temp;

	temp.x = kTileSize*undefined;
	temp.y = 0;
	temp.w = kTileSize;
	temp.h = kTileSize;
	undefinedTile = surfaceManager->createSurfaceSection(set,temp);

	tiles = new sTile*[w];

	for(x = 0; x < w; ++x){
		tiles[x] = new sTile[h];
	}

	for(y = 0; y < h; ++y){
		for(x = 0; x < w; ++x){
			int tile = 0;
			slen = 0;
			while(((strpos + slen) <= (int)tiledata.length()) && (tiledata[strpos+slen] != ' ')){
				slen++;
			}
			//cout << strpos << " " << slen << " ";
			//cout << tiledata.substr(strpos,slen) << " ";
			tile = strToInt(tiledata.substr(strpos,slen));
			//cout << tile << " ";
			temp.x = kTileSize*tile;
			temp.y = 0;
			temp.w = kTileSize;
			temp.h = kTileSize;
			tiles[x][y].gfx = surfaceManager->createSurfaceSection(set,temp);
			strpos += slen + 1;
		}
		//cout << endl;
	}
	strpos = 0;
	for(y = 0; y < h; ++y){
		for(x = 0; x < w; ++x){
			int type = 0;
			slen = 0;
			while(((strpos + slen) <= (int)coldata.length()) && (coldata[strpos+slen] != ' ')){
				slen++;
			}
			type = strToInt(coldata.substr(strpos,slen));
			switch(type){
				case 0:
					tiles[x][y].type = T_PASSABLE;
					break;
				case 1:
					tiles[x][y].type = T_SOLID;
					break;
				case 2:
					tiles[x][y].type = T_SLOPE_UP;
					break;
				case 3:
					tiles[x][y].type = T_SLOPE_DOWN;
					break;
				default:
					tiles[x][y].type = T_PASSABLE;
			}
			strpos += slen + 1;
		}
	}
	/*cout << width << " " << height << endl;
	for(y = 0; y < h; y++){
		for(x = 0; x < w; x++){
			cout << tiles[x][y].gfx << " ";
		}
		cout << endl;
	}
	cout << endl;
	for(y = 0; y < h; y++){
		for(x = 0; x < w; x++){
			cout << tiles[x][y].type << " ";
		}
		cout << endl;
	}*/
}

cTileMap::~cTileMap(){
	int i;
	for(i = 0; i < w; ++i){
		delete[] tiles[i];
	}
	delete[] tiles;
}

void cTileMap::draw(cDisplay* display, cSurfaceManager* surfaceManager, cCamera* camera){
	int x, y;

	int cw = display->getW(), ch = display->getH(); // bottom right
	int cx = camera->getX()-(cw/2), cy = camera->getY()-(ch/2); // changes camera to top left rather than center
	

	// for some reason it doesn't want to display tiles less than 0 unless you can see ALL of them... why?
	// quick fix: add - 1 to x and y.
	for(y = cy/kTileSize - 1; y < ((cy+ch)/kTileSize + 1); ++y){
		/*if(y < 0){
			y = 0;
		}*/
		for(x = cx/kTileSize - 1; x < ((cx+cw)/kTileSize + 1); ++x){
			/*if(x < 0){
				x = 0;
			}*/
			if(x < 0 || y < 0 || x >= w || y >= h){
				surfaceManager->drawSurfaceSection(display, undefinedTile, x*kTileSize - cx, y*kTileSize - cy);
			} else {
				surfaceManager->drawSurfaceSection(display, tiles[x][y].gfx, x*kTileSize - cx, y*kTileSize - cy);
			}
		}
	}
}

eTileType cTileMap::tileType(int x, int y){
	if(x < kTileSize*w && x >= 0 && y >= 0 && y < kTileSize*h){
		return tiles[x/16][y/16].type;
	}
	return T_PASSABLE;
}

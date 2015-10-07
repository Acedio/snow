CC=g++
CFLAGS=-c -Wall

all: snow

snow: globals.o graphics.o tileMap.o input.o camera.o timer.o objectManager.o object.o player.o game.o snow.o snow.cpp
	$(CC) globals.o graphics.o tileMap.o input.o camera.o timer.o objectManager.o object.o player.o game.o snow.o tinyxml.o tinyxmlerror.o tinyxmlparser.o tinystr.o -lSDL -lSDL_image -o snow

globals.o: globals.cpp globals.h
	$(CC) $(CFLAGS) globals.cpp

game.o: graphics.o tileMap.o game.cpp game.h
	$(CC) $(CFLAGS) game.cpp tinyxml/tinyxml.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinystr.cpp

tileMap.o: graphics.o camera.o tileMap.cpp tileMap.h
	$(CC) $(CFLAGS) tileMap.cpp

graphics.o: graphics.cpp graphics.h
	$(CC) $(CFLAGS) graphics.cpp

input.o: graphics.o input.cpp input.h
	$(CC) $(CFLAGS) input.cpp

camera.o: object.o camera.cpp camera.h
	$(CC) $(CFLAGS) camera.cpp

timer.o: timer.cpp timer.h
	$(CC) $(CFLAGS) timer.cpp

objectManager.o: object.o objectManager.cpp objectManager.h
	$(CC) $(CFLAGS) objectManager.cpp

object.o: object.cpp object.h
	$(CC) $(CFLAGS) object.cpp

player.o: input.o graphics.o object.o player.cpp player.h
	$(CC) $(CFLAGS) player.cpp

clean:
	rm -rf *.o snow

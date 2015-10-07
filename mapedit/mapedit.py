import pygame, sys, time
from xml.dom import minidom
import StringIO

TILESIZE = 16
NUMTILES = 16

WINDOW_W = 320
WINDOW_H = 240
WINDOW_W_TILES = 20
WINDOW_H_TILES = 15

MAXCOL = 1

def prtmap(screen, arr, rect, tileSet):
	if(rect.top + WINDOW_H_TILES > len(arr)):
		yRange = range(rect.top, len(arr))
	else:
		yRange = range(rect.top, rect.top + WINDOW_H_TILES)
	if(rect.left + WINDOW_W_TILES > len(arr[0])):
		xRange = range(rect.left, len(arr[0]))
	else:
		xRange = range(rect.left, rect.left + WINDOW_W_TILES)
	for y in yRange:
		for x in xRange:
			screen.blit(tileSet,((x-rect.left)*TILESIZE,(y-rect.top)*TILESIZE),pygame.Rect(arr[y][x]*TILESIZE, 0, TILESIZE, TILESIZE))
			# screen.blit(tileSet,((x-rect.left)*TILESIZE,(y-rect.top)*TILESIZE),pygame.Rect((arr[y][x] & 15)*TILESIZE, (arr[y][x] >> 4)*TILESIZE,TILESIZE,TILESIZE))

def prtcol(screen, arr, rect):
	if(rect.top + WINDOW_H_TILES > len(arr)):
		yRange = range(rect.top, len(arr))
	else:
		yRange = range(rect.top, rect.top + WINDOW_H_TILES)
	if(rect.left + WINDOW_W_TILES > len(arr[0])):
		xRange = range(rect.left, len(arr[0]))
	else:
		xRange = range(rect.left, rect.left + WINDOW_W_TILES)
	for y in yRange:
		for x in xRange:
			if(arr[y][x] == 1):
				pygame.draw.rect(screen, (255,0,0), pygame.Rect((x-rect.left)*TILESIZE,(y-rect.top)*TILESIZE,TILESIZE,TILESIZE),1)
			elif(arr[y][x] == 2):
				pygame.draw.polygon(screen, (255,0,0), (((x-rect.left)*TILESIZE,(y-rect.top+1)*TILESIZE - 1),((x-rect.left+1)*TILESIZE - 1,(y-rect.top)*TILESIZE),((x-rect.left+1)*TILESIZE - 1,(y-rect.top+1)*TILESIZE - 1)), 1)
			elif(arr[y][x] == 3):
				pygame.draw.polygon(screen, (255,0,0), (((x-rect.left)*TILESIZE,(y-rect.top+1)*TILESIZE - 1),((x-rect.left)*TILESIZE,(y-rect.top)*TILESIZE),((x-rect.left+1)*TILESIZE - 1,(y-rect.top+1)*TILESIZE - 1)), 1)

def prtset(screen, rect, tileSet):
	pygame.draw.rect(screen, (255,0,0), pygame.Rect(rect.x+TILESIZE,rect.y,TILESIZE,TILESIZE),1)
	pygame.draw.polygon(screen, (255,0,0), ((rect.x + 2*TILESIZE, rect.y + TILESIZE - 1),(rect.x + 3*TILESIZE - 1, rect.y + TILESIZE - 1),(rect.x + 3*TILESIZE - 1,rect.y)), 1)
	pygame.draw.polygon(screen, (255,0,0), ((rect.x + 3*TILESIZE, rect.y + TILESIZE - 1),(rect.x + 4*TILESIZE - 1, rect.y + TILESIZE - 1),(rect.x + 3*TILESIZE,rect.y)), 1)
	for x in range(2): #int((tileSet.get_width()+TILESIZE*16-1)/(TILESIZE*16))):
		screen.blit(tileSet,(rect.x,TILESIZE+rect.y+x*TILESIZE),pygame.Rect(x*16*TILESIZE,0,TILESIZE*16,TILESIZE))

def tilePos(pos):
	return (pos[0] >> 4, pos[1] >> 4);

def prepareData(width, height, arr):
	data = ""
	for y in range(height):
		for x in range(width):
			toWrite = str(arr[y][x])
			toWrite += " "
			data += toWrite
	return data

def makeArr(width, height):
	arr = [None]*height

	for i in range(height):
		arr[i] = [None] * width 

	return arr

# MAIN CODE

file = ""

tileSetFile = ""

tileSet = pygame.image

level = minidom.Document()

width, height = 0, 0

quit = False

if len(sys.argv) > 1:
	file = sys.argv[1]
else:
	file = raw_input("What file to edit? ")

try:
	level = minidom.parse(file)
	
	width = level.getElementsByTagName("map")[0].getElementsByTagName("width")[0].firstChild.data
	height = level.getElementsByTagName("map")[0].getElementsByTagName("height")[0].firstChild.data
	width, height = int(width), int(height)

	arr = makeArr(width, height)
	data = level.getElementsByTagName("map")[0].getElementsByTagName("tiledata")[0].firstChild.data
	datasock = StringIO.StringIO(data)

	temparr = datasock.readline().split()
	i = 0

	for y in range(height):
		for x in range(width):
			arr[y][x] = int(temparr[i])
			i += 1
	datasock.close()

	colarr = makeArr(width, height)
	data = level.getElementsByTagName("map")[0].getElementsByTagName("coldata")[0].firstChild.data
	datasock = StringIO.StringIO(data)

	temparr = datasock.readline().split()
	i = 0

	for y in range(height):
		for x in range(width):
			colarr[y][x] = int(temparr[i])
			i += 1
	datasock.close()
except IOError:
	answer = raw_input("File \"" + file + "\" doesn't exist, would you like to create it? (Y\N) ")
	if(answer == "y" or "Y"):
		width = int(raw_input("Width? "))
		height = int(raw_input("Height? "))
		tileSetFile = raw_input("Tile set? ")
		arr = makeArr(width, height)
		for y in range(height):
			for x in range(width):
				arr[y][x] = 0
		colarr = makeArr(width, height)
		for y in range(height):
			for x in range(width):
				colarr[y][x] = 0
		level.appendChild(level.createElement("level"))
		level.getElementsByTagName("level")[0].appendChild(level.createElement("map"))
		level.getElementsByTagName("level")[0].getElementsByTagName("map")[0].appendChild(level.createElement("width"))
		level.getElementsByTagName("level")[0].getElementsByTagName("map")[0].appendChild(level.createElement("height"))
		level.getElementsByTagName("level")[0].getElementsByTagName("map")[0].appendChild(level.createElement("tiledata"))
		level.getElementsByTagName("level")[0].getElementsByTagName("map")[0].appendChild(level.createElement("coldata"))
		level.getElementsByTagName("level")[0].getElementsByTagName("map")[0].appendChild(level.createElement("tileset"))
		level.getElementsByTagName("level")[0].getElementsByTagName("map")[0].getElementsByTagName("width")[0].appendChild(level.createTextNode(str(width)))
		level.getElementsByTagName("level")[0].getElementsByTagName("map")[0].getElementsByTagName("height")[0].appendChild(level.createTextNode(str(height)))
		level.getElementsByTagName("level")[0].getElementsByTagName("map")[0].getElementsByTagName("tiledata")[0].appendChild(level.createTextNode(str(prepareData(width,height,arr))))
		level.getElementsByTagName("level")[0].getElementsByTagName("map")[0].getElementsByTagName("coldata")[0].appendChild(level.createTextNode(str(prepareData(width,height,colarr))))
		level.getElementsByTagName("level")[0].getElementsByTagName("map")[0].getElementsByTagName("tileset")[0].appendChild(level.createTextNode(tileSetFile))
	elif(answer == "n" or "N"):
		quit = True
	else:
		print "Quitting!"
		quit = True

pygame.init()

screen = pygame.display.set_mode((WINDOW_W + TILESIZE*NUMTILES,WINDOW_H))

pygame.display.set_caption("Snow MapEdit", "")

curTile = 0
curCol = 0
dispCol = True
xTileOffset = 0
yTileOffset = 0

tileSetFile = level.getElementsByTagName("map")[0].getElementsByTagName("tileset")[0].firstChild.data
tileSet = pygame.image.load(level.getElementsByTagName("map")[0].getElementsByTagName("tileset")[0].firstChild.data)

prtmap(screen, arr, pygame.Rect(0,0,0,0),tileSet)
if dispCol:
	prtcol(screen, colarr, pygame.Rect(0,0,0,0))
prtset(screen, pygame.Rect(WINDOW_W,0,0,0),tileSet)
pygame.display.flip()

while not quit:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			quit = True
			pygame.quit()
		elif event.type == pygame.KEYDOWN:
			if(event.key == pygame.K_s):
				towrite = open(file,"w")
				level.getElementsByTagName("map")[0].getElementsByTagName("width")[0].firstChild.data = width
				level.getElementsByTagName("map")[0].getElementsByTagName("height")[0].firstChild.data = height
				level.getElementsByTagName("map")[0].getElementsByTagName("tileset")[0].firstChild.data = tileSetFile
				level.getElementsByTagName("map")[0].getElementsByTagName("tiledata")[0].firstChild.data = prepareData(width,height,arr)
				level.getElementsByTagName("map")[0].getElementsByTagName("coldata")[0].firstChild.data = prepareData(width,height,colarr)
				towrite.write(level.toxml())
				towrite.close()
				print "Written!"
			elif(event.key == pygame.K_c):
				dispCol = not dispCol
	if not quit:
		if(pygame.mouse.get_pressed()[0] == 1):
			mouseX, mouseY = tilePos(pygame.mouse.get_pos())
			if(mouseX < WINDOW_W_TILES):
				arr[mouseY + yTileOffset][mouseX + xTileOffset] = curTile
				colarr[mouseY + yTileOffset][mouseX + xTileOffset] = curCol
			elif(mouseY > TILESIZE & mouseY < TILESIZE*NUMTILES):
				curTile = (mouseX - WINDOW_W_TILES)+((mouseY-1) << 4)
				print curTile
			else:
				curCol = (mouseX - WINDOW_W_TILES)
				print curCol
			screen.fill((0,0,0))
			prtmap(screen, arr, pygame.Rect(xTileOffset,yTileOffset,0,0),tileSet)
			if dispCol:
				prtcol(screen, colarr, pygame.Rect(xTileOffset,yTileOffset,0,0))
			prtset(screen, pygame.Rect(WINDOW_W,0,0,0),tileSet)
			pygame.display.flip()
		if(pygame.mouse.get_pressed()[2] == 1):
			mouseX, mouseY = tilePos(pygame.mouse.get_pos())
			if(mouseX < WINDOW_W_TILES):
				colarr[mouseY + yTileOffset][mouseX + xTileOffset] += 1
				if(colarr[mouseY + yTileOffset][mouseX + xTileOffset] > MAXCOL):
					colarr[mouseY + yTileOffset][mouseX + xTileOffset] = 0
			screen.fill((0,0,0))
			prtmap(screen, arr, pygame.Rect(xTileOffset,yTileOffset,0,0),tileSet)
			if dispCol:
				prtcol(screen, colarr, pygame.Rect(xTileOffset,yTileOffset,0,0))
			prtset(screen, pygame.Rect(WINDOW_W,0,0,0),tileSet)
			pygame.display.flip()
			while(pygame.mouse.get_pressed()[2] == 1):
				time.sleep(.01)
				pygame.event.pump()
		keystates = pygame.key.get_pressed()
		if(keystates[pygame.K_UP]):
			yTileOffset -= 1
			if(yTileOffset < 0):
				yTileOffset = 0
		elif(keystates[pygame.K_DOWN]):
			yTileOffset += 1
			if(yTileOffset > height - WINDOW_H_TILES):
				yTileOffset = height - WINDOW_H_TILES
		elif(keystates[pygame.K_LEFT]):
			xTileOffset -= 1
			if(xTileOffset < 0):
				xTileOffset = 0
		elif(keystates[pygame.K_RIGHT]):
			xTileOffset += 1
			if(xTileOffset > width - WINDOW_W_TILES):
				xTileOffset = width - WINDOW_W_TILES
		screen.fill((0,0,0))
		prtmap(screen, arr, pygame.Rect(xTileOffset,yTileOffset,0,0),tileSet)
		if dispCol:
				prtcol(screen, colarr, pygame.Rect(xTileOffset,yTileOffset,0,0))
		prtset(screen, pygame.Rect(WINDOW_W,0,0,0),tileSet)
		pygame.display.flip()
		time.sleep(.01)

#pragma once
#include "Tile.h"
#include <math.h>
#include <string>
#include "Player.h"

#define WIDTH 48
#define HEIGHT 24
#define VIEWRADIUS 5

class Map
{
private:
	int seed;
	int id;

public:
	Tile tiles[HEIGHT][WIDTH];
	Player player;
private:

public:
	//void setSeed(const int& seed);
	//int getSeed();

	Map();
	Map(Player pl);
	void updateVisibleTiles();
	char getCharAt(const int& y, const int& x);
	//std::string drawLine(const int& y);
	void drawMap();
};


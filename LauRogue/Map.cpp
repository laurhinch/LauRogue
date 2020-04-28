#include "Map.h"
#include <math.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>

Map::Map() {
	player = Player();
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			tiles[i][j] = Tile('#');
		}
	}
}

Map::Map(Player pl) {
	player = pl;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			tiles[i][j] = Tile('#');
		}
	}
}

void Map::updateVisibleTiles() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			//check if tile is within a circle around the player coordinates
			tiles[i][j].setVisible(!(pow(j - player.getX(), 2) + pow(i - player.getY(), 2) > pow(VIEWRADIUS, 2)));
		}
	}
}

char Map::getCharAt(const int& y, const int& x) {
	if (player.getX() == x && player.getY() == y) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		return '@';
	}
	return tiles[y][x].draw();
}

/*
std::string Map::drawLine(const int& y) {
	std::string str = "";
	for (int i = 0; i < WIDTH; i++) {
		str += getCharAt(y, i);
	}
	return str;
}
*/
void Map::drawMap() {
	updateVisibleTiles();
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			printf("%c", getCharAt(y, x));
		}
		printf("\n");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


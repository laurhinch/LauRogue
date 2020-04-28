#include "Tile.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

char Tile::getType() {
	return tileType;
}

void Tile::setType(char type) {
	tileType = type;
}

bool Tile::isVisible() {
	return visible;
}

void Tile::setVisible(bool visible) {
	this->visible = visible;
}

Tile::Tile() {
	this->tileType = ' ';
	this->visible = false;
}

Tile::Tile(char type) {
	this->tileType = type;
	this->visible = true;
}

Tile::Tile(char type, bool visible) {
	this->tileType = type;
	this->visible = visible;
}

char Tile::draw() {
	if (!visible) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		return '?';
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	return tileType;
}
#include "Tile.h"

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
	return visible ? tileType : ' ';
}
#pragma once
class Tile
{
private:
	char tileType;
	bool visible;
public:

private:

public:
	char getType();
	void setType(char type);

	bool isVisible();
	void setVisible(bool visible);

	Tile();
	Tile(char type);
	Tile(char type, bool visible);

	char draw();
};


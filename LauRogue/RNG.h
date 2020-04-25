#pragma once

class RNG
{
private:
	int seed;

public:

private:

public:
	RNG();
	RNG(int seed);

	int randInt(int& min, int& max);
	int luckInt(int& min, int& max, int& luck);

};


#include "RNG.h"

#include <cstdlib>
#include <math.h>

RNG::RNG() {
    this->seed = 1;
};

RNG::RNG(int seed) {
    this->seed = seed;
};

//rng (inclusive)
int RNG::randInt(int& min, int& max) {
    return rand() % (max - min + 1) + min;
};

//rng with luck (inclusive)
int RNG::luckInt(int& min, int& max, int& luck) {
    if (luck == 0) { return 0; }
    int x = rand() % (max - min + 1) + min;
    double a = 2 / (double)luck;
    double b = (double)x - max;
    double val = a * b + max;
    if (val < 0) { return 0; }
    return (int)ceil(val);
}
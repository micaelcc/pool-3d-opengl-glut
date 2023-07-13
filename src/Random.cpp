#include "../include/random.h"

int Random::generateRandom(int limitB, int limitA)
{
    int randomValue = rand() % (limitB - limitA + 1) + limitA;
    return randomValue;
}
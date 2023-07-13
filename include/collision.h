#pragma once
#include "ball.h"
#define CLOTH_HEIGHT 1.0076

class Collision
{
public:
    static float getDistance(Point *, Point *);
    static bool checkCollision(Ball *, Ball *);
    static void updateSpeeds(Ball *, Ball *);
};
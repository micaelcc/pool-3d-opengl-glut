#pragma once
#include "point.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Geometry
{
public:
    static void scale(Point *, float, float, float);
    static void translate(Point *, float, float, float);
    static void rotate(Point *, float, float, float, float);
    static Point *calculeProjection(Point A, Point B);
};
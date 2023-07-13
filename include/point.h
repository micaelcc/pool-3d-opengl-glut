#pragma once
#include "glm/glm.hpp"

class Point
{
public:
    float x, y, z;

    Point(float, float, float);

    glm::vec3 toArray();
};
#include "../include/point.h"

Point::Point(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

glm::vec3 Point::toArray()
{
	return glm::vec3(this->x, this->y, this->z);
}
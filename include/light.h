#pragma once
#include "vector"
#include "glm/glm.hpp"
#include "math.h"
#include "GL/gl.h"
#include "point.h"

typedef struct
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shine;
} Components;

class Light
{
private:
    Point *position;
    Components *components;
    static Light *instance;

public:
    Light(Point, glm::vec3, glm::vec3, glm::vec3, float);

    Point *getPosition();
    glm::vec3 getDiffuse();
    glm::vec3 getAmbient();
    glm::vec3 getSpecular();
    glm::vec3 lighting(
        Point point,
        Point cameraPos,
        glm::vec3 ambientMaterial,
        glm::vec3 diffuseMaterial,
        glm::vec3 specularMaterial,
        float shineMaterial,
        glm::vec3 normal);

    static void enableNativeLighting(
        glm::vec3 ambientMaterial,
        glm::vec3 diffuseMaterial,
        glm::vec3 specularMaterial,
        float shineMaterial);
    static glm::vec3 getNormalTriangle(Point, Point, Point);
    static Light *getInstance();
};
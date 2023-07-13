#pragma once
#include "string"
#include "SOIL/SOIL.h"
#include "iostream"
#include "GL/glut.h"
#include "vector"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Texture
{
private:
    GLuint texture;

public:
    void load(std::string path);

    GLuint getTexture();
};
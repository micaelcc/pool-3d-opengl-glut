#pragma once
#define MODEL_VERTEX_SCALE 0.01

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "glm/glm.hpp"

#include "texture.h"
#include "light.h"

extern Point *cameraPosition;

class Model
{
public:
    Texture *tex;
    const aiScene *scene;
    Components *ambientComponents;
    void renderByNode(aiNode *noldde);

public:
    Model();
    void load(
        std::string pathModel,
        std::string pathTexture,
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular,
        float shine);
    void render();
};
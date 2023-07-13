#include "../include/texture.h"
#include "light.h"

class Floor
{
private:
    Texture *tex;

public:
    Floor(std::string texturePath);
    void draw();
};
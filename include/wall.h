#include "texture.h"
#include "light.h"

class Wall
{
private:
    std::vector<Texture *> textures;

    void drawBrickWalls();
    void drawCeramicWalls();
    void drawBrickQuad();
    void drawCeramicQuad();

public:
    Wall(std::string texturePath1, std::string texturePath2);
    void draw();
};
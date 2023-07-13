#include "../include/floor.h"

Floor::Floor(std::string texturePath)
{
    this->tex = new Texture();

    this->tex->load(texturePath);
}

void Floor::draw()
{
    if (!this->tex)
        return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->tex->getTexture());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repetição horizontal
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repetição vertical
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);

    Light::enableNativeLighting(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 30);

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);

    glColor3f(1, 1, 1);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-6, 0, -6);
    glTexCoord2f(6.0, 0.0);
    glVertex3f(6, 0, -6);
    glTexCoord2f(6.0, 6.0);
    glVertex3f(6, 0, 6);
    glTexCoord2f(0.0, 6.0);
    glVertex3f(-6, 0, 6);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
}
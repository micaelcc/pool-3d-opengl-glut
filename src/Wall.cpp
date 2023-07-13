#include "../include/wall.h"
#include <glm/ext.hpp>

Wall::Wall(std::string texturePath1, std::string texturePath2)
{
    this->textures = {new Texture(), new Texture()};
    this->textures[0]->load(texturePath1);
    this->textures[1]->load(texturePath2);
}

void Wall::drawCeramicQuad()
{
    glBegin(GL_QUADS);

    glColor3f(1, 1, 1);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-4, -4, 0);
    glTexCoord2f(4.0, 0.0);
    glVertex3f(10, -4, 0);
    glTexCoord2f(4.0, 2);
    glVertex3f(10, -4, 5);
    glTexCoord2f(0.0, 2);
    glVertex3f(-4, -4, 5);
    glEnd();
}

void Wall::drawBrickQuad()
{
    glBegin(GL_QUADS);

    glColor3f(1, 1, 1);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-4, -4, 0);
    glTexCoord2f(8.0, 0.0);
    glVertex3f(10, -4, 0);
    glTexCoord2f(8.0, 3);
    glVertex3f(10, -4, 5);
    glTexCoord2f(0.0, 3);
    glVertex3f(-4, -4, 5);
    glEnd();
}

void Wall::drawBrickWalls()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->textures[0]->getTexture());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repetição horizontal
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repetição vertical

    glNormal3f(0.0, 1.0, 0.0);

    this->drawBrickQuad();

    glNormal3f(0.0, -1.0, 0.0);

    glPushMatrix();
    glTranslatef(0, 14, 0);
    this->drawBrickQuad();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void Wall::drawCeramicWalls()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->textures[1]->getTexture());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repetição horizontal
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repetição vertical

    glNormal3f(1.0, 0.0, 0.0);

    glPushMatrix();
    glTranslatef(0, 6, 0);
    glRotatef(-90, 0, 0, 1);
    this->drawCeramicQuad();
    glPopMatrix();

    glNormal3f(-1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(6, 0, 0);
    glRotatef(90, 0, 0, 1);
    this->drawCeramicQuad();
    glPopMatrix();
}

void Wall::draw()
{
    if (!this->textures[0] || !this->textures[1])
        return;

    Light::enableNativeLighting(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 100);

    this->drawBrickWalls();
    this->drawCeramicWalls();

    glDisable(GL_LIGHTING);
}
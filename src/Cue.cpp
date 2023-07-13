#include "../include/cue.h"

Cue::Cue(std::string modelPath, std::string texturePath)
{
    this->position = new Point(-1, -1, -1);
    this->direction = new Point(-1, -1, 1);

    this->visible = true;

    this->aim_direction = {
        new Point(-1, -1, 1),
        new Point(-1, -1, 1)};

    this->isAimEnable = false;

    this->model = new Model();
    this->model->load(modelPath, texturePath, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 50);
}

void Cue::draw(Point *whiteBallPosition)
{
    if (!this->visible || !this->model)
        return;

    glPushMatrix();
    glTranslatef(whiteBallPosition->x, whiteBallPosition->y, whiteBallPosition->z);
    glRotatef(this->mouseX, 0.0, 0.0f, 1.0f);
    glRotatef(2, 0.0, 1.0f, 0.0f);
    glTranslatef((0.65 + (this->appliedForce * 0.5)) * -1, 0.0f, 0.0f);
    glScalef(0.02, 0.02, 0.02);
    glColor3f(1, 1, 1);

    this->model->render();
    glPopMatrix();
}

void Cue::onMouseMove(float mouseX)
{
    this->mouseX = mouseX;
}

void Cue::onAppliedForce(float force)
{
    this->appliedForce = force;
}

void Cue::attDirection(Point *ball_position)
{
    this->direction = Geometry::calculeProjection(*ball_position, *this->position);
}

void Cue::attPosition(Point *p)
{
    this->position = p;
}

bool Cue::isVisible()
{
    return this->visible;
}

Point *Cue::getPosition()
{
    return this->position;
}

void Cue::setIsVisible(bool visible)
{
    if (!visible)
        this->appliedForce = 0;

    this->visible = visible;
}

Point *Cue::getDirection()
{
    return this->direction;
}

void Cue::setAimEnable(bool status)
{
    this->isAimEnable = status;
}
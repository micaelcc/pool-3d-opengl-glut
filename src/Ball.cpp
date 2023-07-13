#include "../include/ball.h"

Ball::Ball(float x, float y, float z, BallTypes type, std::string texturePath, bool list = false)
{
    this->position = new Point(x, y, z);
    this->speedX = 0;
    this->speedY = 0;
    this->direction = new Point(-1, -1, 0);
    this->list = list;
    this->type = type;
    this->enabled = true;
    this->tex = new Texture();
    this->tex->load(texturePath);
    this->quadric = gluNewQuadric();
    this->actuallyRotationAngle = 0;
    this->lastRotationAngle = 0;
}

Point *Ball::getPosition()
{
    return this->position;
}

void Ball::disable()
{
    this->speedX = 0;
    this->speedY = 0;
    this->position->x = -1;
    this->position->y = -1;
    this->position->z = -1;

    this->enabled = false;
}

void Ball::enable()
{
    this->enabled = true;
}

void Ball::draw()
{

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->tex->getTexture());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    gluQuadricTexture(this->quadric, GL_TRUE);

    Light::enableNativeLighting(glm::vec3(0.5, 0.5, 0.5), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 30);

    glPushMatrix();
    glTranslatef(this->position->x, this->position->y, this->position->z);

    float rotation = this->isMoving() ? this->actuallyRotationAngle : this->lastRotationAngle;

    glRotatef(rotation, 0.0f, 1.0f, 0.0f);
    gluSphere(this->quadric, BALL_RADIUS, BALL_SLICES, BALL_STACKS);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_LIGHTING);
}

void Ball::updateRotationAngle()
{
    if (this->isMoving())
    {
        this->lastRotationAngle = this->actuallyRotationAngle;
        this->actuallyRotationAngle = 0;
    }

    glm::vec3 direction = glm::vec3(this->direction->x, this->direction->y, this->direction->z) - glm::vec3(this->position->x, this->position->y, this->position->z);
    glm::vec3 normal = glm::normalize(direction);

    float angle = atan2(normal.y, normal.x) * (180.0 / M_PI);
    this->actuallyRotationAngle = ROTATION_FACTOR * angle;
}

void Ball::setPosition(float x, float y, float z)
{
    this->position->x = x;
    this->position->y = y;
    this->position->z = z;
}

void Ball::moveBall()
{
    float ballSpeedX = this->getSpeedX();
    float ballSpeedY = this->getSpeedY();

    float ballRadius = BALL_RADIUS;

    if (ballSpeedX <= 0.0001f && ballSpeedX >= -0.0001f && ballSpeedY <= 0.0001f && ballSpeedY >= -0.0001f)
    {
        this->setSpeed(0, 0);
        return;
    }

    float ballPositionX = this->position->x;
    float ballPositionY = this->position->y;

    ballSpeedX *= 0.995;
    ballSpeedY *= 0.995;

    if (ballPositionY <= EDGE_VERTICAL_Y_MAX && ballPositionY >= EDGE_VERTICAL_Y_MIN)
    {
        if (
            (ballPositionX + ballRadius > TABLE_X_MAX || ballPositionX - ballRadius < TABLE_X_MIN))
        {
            this->position->x -= (ballSpeedX);

            ballSpeedX = ballSpeedX * -1;
        }
    }

    if (
        (ballPositionX >= EDGE_HORIZONTAL_X1_MIN && ballPositionX <= EDGE_HORIZONTAL_X1_MAX) || (ballPositionX >= EDGE_HORIZONTAL_X2_MIN && ballPositionX <= EDGE_HORIZONTAL_X2_MAX))
    {
        if (ballPositionY + ballRadius > TABLE_Y_MAX || ballPositionY - ballRadius < TABLE_Y_MIN)
        {
            this->position->y -= (ballSpeedY);
            ballSpeedY = ballSpeedY * -1;
        }
    }

    this->position->x += (ballSpeedX);
    this->position->y += (ballSpeedY);

    this->setSpeed(ballSpeedX, ballSpeedY);
}

float Ball::getRadius()
{
    return BALL_RADIUS;
}

bool Ball::isEnabled()
{
    return this->enabled;
}

void Ball::setSpeed(float speedX, float speedY)
{
    this->speedX = speedX;
    this->speedY = speedY;
}

void Ball::setDirection(float x, float y, float z, float force)
{
    this->direction->x = x;
    this->direction->y = y;
    this->direction->z = z;

    this->initSpeeds(force);
}

void Ball::initSpeeds(float force)
{
    force = force * FORCE_FACTOR;

    float distancia = sqrt(
        pow(this->direction->x - this->position->x, 2) +
        pow(this->direction->y - this->position->y, 2));

    float dx = (this->direction->x - this->position->x) / distancia;
    float dy = (this->direction->y - this->position->y) / distancia;

    this->speedX = (force * dx);
    this->speedY = (force * dy);
}

bool Ball::isMoving()
{
    return this->speedX != 0 || this->speedY != 0;
}

float Ball::getSpeedX()
{
    return this->speedX;
}

float Ball::getSpeedY()
{
    return this->speedY;
}

BallTypes Ball::getType()
{
    return this->type;
}
#include "../include/collision.h"

void Collision::updateSpeeds(Ball *A, Ball *B)
{
    float distance = getDistance(A->getPosition(), B->getPosition());

    float ballAPositionX = A->getPosition()->x;
    float ballAPositionY = A->getPosition()->y;
    float ballBPositionX = B->getPosition()->x;
    float ballBPositionY = B->getPosition()->y;
    float ballASpeedX = A->getSpeedX();
    float ballASpeedY = A->getSpeedY();
    float ballBSpeedX = B->getSpeedX();
    float ballBSpeedY = B->getSpeedY();

    // vetor normal entre as esferas
    float nx = (ballBPositionX - ballAPositionX) / distance;
    float ny = (ballBPositionY - ballAPositionY) / distance;

    // calcula diferenças de velocidades
    float kx = (ballASpeedX - ballBSpeedX);
    float ky = (ballASpeedY - ballBSpeedY);

    // vetor escalar da colisao
    float p = 2.0 * (nx * kx + ny * ky) / (BALL_RADIUS * 2);

    A->setSpeed(
        ballASpeedX - p * BALL_RADIUS * nx,
        ballASpeedY - p * BALL_RADIUS * ny);

    B->setSpeed(
        ballBSpeedX + p * BALL_RADIUS * nx,
        ballBSpeedY + p * BALL_RADIUS * ny);
}

float Collision::getDistance(Point *A, Point *B)
{
    float distanceX = A->x - B->x;
    float distanceY = A->y - B->y;

    return sqrt(pow(distanceX, 2) + pow(distanceY, 2));
}

bool Collision::checkCollision(Ball *A, Ball *B)
{
    float ballAPositionX = A->getPosition()->x;
    float ballAPositionY = A->getPosition()->y;
    float ballBPositionX = B->getPosition()->x;
    float ballBPositionY = B->getPosition()->y;

    float distanceX = ballAPositionX - ballBPositionX;
    float distanceY = ballAPositionY - ballBPositionY;

    float distanceAB = getDistance(A->getPosition(), B->getPosition());

    float overlap = -(distanceAB - BALL_RADIUS * 2) / 2;

    if (abs(distanceAB) < BALL_RADIUS * 2)
    {
        ballAPositionX += overlap * (distanceX) / distanceAB;
        ballAPositionY += overlap * (distanceY) / distanceAB;

        ballBPositionX -= overlap * (distanceX) / distanceAB;
        ballBPositionY -= overlap * (distanceY) / distanceAB;

        A->setPosition(ballAPositionX, ballAPositionY, CLOTH_HEIGHT);
        B->setPosition(ballBPositionX, ballBPositionY, CLOTH_HEIGHT);

        return true;
    }

    return false;
}
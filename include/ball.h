#pragma once
#include "GL/glut.h"
#include "math.h"
#include "string"
#include "point.h"
#include "texture.h"
#include "light.h"
#define BALL_RADIUS 0.027
#define BALL_STACKS 150
#define BALL_SLICES 150
#define FORCE_FACTOR 0.05
#define ROTATION_FACTOR -100
#define TABLE_X_MAX 4.083
#define TABLE_Y_MIN 2.533
#define TABLE_X_MIN 2.175
#define TABLE_Y_MAX 3.483
#define EDGE_VERTICAL_Y_MAX 3.43
#define EDGE_VERTICAL_Y_MIN 2.59
#define EDGE_HORIZONTAL_X1_MAX 3.08
#define EDGE_HORIZONTAL_X1_MIN 2.235
#define EDGE_HORIZONTAL_X2_MAX 4.03
#define EDGE_HORIZONTAL_X2_MIN 3.185

enum BallTypes
{
    BALL_8 = 1,
    WHITE_CUE_BALL = 0,
    COLORED_BALL = 3
};

class Ball
{
private:
    Point *position;
    Point *direction;
    float speedX;
    float speedY;
    BallTypes type;
    bool list;
    bool enabled;
    Texture *tex;
    GLUquadricObj *quadric;
    float lastRotationAngle;
    float actuallyRotationAngle;

public:
    Ball(float, float, float, BallTypes, std::string, bool);
    void moveBall();
    void draw();
    void disable();
    void initSpeeds(float);
    void setPosition(float, float, float);
    void setSpeed(float, float);
    void setDirection(float, float, float, float);
    void enable();
    void updateRotationAngle();
    Point *getPosition();
    float getRadius();
    float getSpeedX();
    float getSpeedY();
    bool isMoving();
    bool isEnabled();
    BallTypes getType();
};
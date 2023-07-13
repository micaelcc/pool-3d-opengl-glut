#include "vector"
#include "model.h"
#include "GL/glut.h"
#include "math.h"
#include "glm/glm.hpp"
#include "geometry.h"
#include "point.h"

class Cue
{
private:
    Point *position;
    Point *direction;
    bool visible;
    bool isAimEnable;
    std::vector<Point *> aim_direction;
    Model *model;
    float appliedForce = 0;
    float mouseX = 0;

public:
    Cue(std::string modelPath, std::string texturePath);
    void draw(Point *p);
    void onMouseMove(float);
    void attDirection(Point *);
    void attPosition(Point *);
    void onAppliedForce(float);
    void setIsVisible(bool);
    void setAimEnable(bool);
    Point *getDirection();
    Point *getPosition();
    bool isVisible();
};
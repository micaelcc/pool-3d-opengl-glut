#include "../include/geometry.h"

void Geometry::scale(Point *p, float scaleX, float scaleY, float scaleZ)
{
    p->x *= scaleX;
    p->y *= scaleY;
    p->z *= scaleZ;
}

void Geometry::translate(Point *p, float translateX, float translateY, float translateZ)
{
    p->x += translateX;
    p->y += translateY;
    p->z += translateZ;
}

void Geometry::rotate(Point *p, float angle, float rotateX, float rotateY, float rotateZ)
{
    glm::mat4 rotationMatrix(1.0f);

    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), glm::vec3(rotateX, rotateY, rotateZ));

    glm::vec4 pointVector(p->x, p->y, p->z, 1.0f);
    glm::vec4 rotatedVector = rotationMatrix * pointVector;

    p->x = rotatedVector.x;
    p->y = rotatedVector.y;
    p->z = rotatedVector.z;
}

Point *Geometry::calculeProjection(Point A, Point B)
{
    // Vetor AB
    float AB_x = B.x - A.x;
    float AB_y = B.y - A.y;
    float AB_z = B.z - A.z;

    // Produto escalar entre AB e A - B
    float dotProduct = AB_x * (A.x - B.x) + AB_y * (A.y - B.y) + AB_z * (A.z - B.z);

    // Produto escalar entre AB e ele mesmo
    float AB_squaredLength = AB_x * AB_x + AB_y * AB_y + AB_z * AB_z;

    // Calcula projecao
    Point *C = new Point(1, 1, 1);

    C->x = A.x + AB_x * dotProduct / AB_squaredLength;
    C->y = A.y + AB_y * dotProduct / AB_squaredLength;
    C->z = A.z;

    return C;
}
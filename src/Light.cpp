#include "../include/light.h"

Light::Light(Point lightPos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shine)
{
    instance = nullptr;
    this->components = new Components({ambient, diffuse, specular, shine});

    this->position = new Point(lightPos);
}

glm::vec3 Light::getAmbient()
{
    return this->components->ambient;
}

glm::vec3 Light::getDiffuse()
{
    return this->components->diffuse;
}

Point *Light::getPosition()
{
    return this->position;
}

glm::vec3 Light::getSpecular()
{
    return this->components->specular;
}

glm::vec3 Light::lighting(
    Point point,
    Point cameraPos,
    glm::vec3 ambientMaterial,
    glm::vec3 diffuseMaterial,
    glm::vec3 specularMaterial,
    float shineMaterial,
    glm::vec3 normal)
{
    glm::vec3 amb = this->components->ambient * ambientMaterial;

    // reflexão difusa
    glm::vec3 l = this->position->toArray() - point.toArray();

    l = glm::normalize(l);
    normal = glm::normalize(normal);

    glm::vec3 dif = this->components->diffuse * diffuseMaterial * glm::max(0.0f, glm::dot(l, normal));

    // reflexão especular
    glm::vec3 v = glm::vec3(cameraPos.toArray()) - point.toArray();

    v = glm::normalize(v);

    glm::vec3 r = 2 * glm::dot(normal, l) * normal - l;

    glm::vec3 esp =
        this->components->specular * specularMaterial * (float)(pow(glm::max(0.0f, glm::dot(v, r)), shineMaterial));

    return amb + dif + esp;
}

glm::vec3 Light::getNormalTriangle(Point A, Point B, Point C)
{
    glm::vec3 n = glm::cross(B.toArray() - A.toArray(), C.toArray() - A.toArray());
    return glm::normalize(n);
}

Light *Light::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Light(Point(3, 3, 5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 100);
    }
    return instance;
}

void Light::enableNativeLighting(glm::vec3 ambientMaterial, glm::vec3 diffuseMaterial, glm::vec3 specularMaterial, float shineMaterial)
{
    // Habilita a iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Define a posição da luz
    GLfloat lightPosition[] = {3, 3, 5, 0.8};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    //  Define as propriedades do material
    GLfloat materialAmbient[] = {ambientMaterial.x, ambientMaterial.y, ambientMaterial.z, 1.0f};
    GLfloat materialDiffuse[] = {diffuseMaterial.x, diffuseMaterial.y, diffuseMaterial.z, 1.0f};
    GLfloat materialSpecular[] = {specularMaterial.x, specularMaterial.y, specularMaterial.z, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, shineMaterial);
}
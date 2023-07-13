#include "../include/model.h"

extern Point *cameraPosition;
void Model::load(std::string pathModel, std::string pathTex, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shine)
{
    this->ambientComponents = new Components({ambient, diffuse, specular, shine});
    this->tex = new Texture();

    this->tex->load(pathTex);

    auto *importer = new Assimp::Importer();

    this->scene = importer->ReadFile(pathModel, aiProcess_Triangulate | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout
            << "Falha ao carregar o modelo: "
            << importer->GetErrorString()
            << std::endl;
        exit(1);
    }
}

void Model::render()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->tex->getTexture());
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);

    aiNode *node = this->scene->mRootNode;

    for (GLuint i = 0; i < node->mNumChildren; i++)
        this->renderByNode(node->mChildren[i]);

    glDisable(GL_TEXTURE_2D);
}

Model::Model()
{
}
void Model::renderByNode(aiNode *node)
{
    for (GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = this->scene->mMeshes[node->mMeshes[i]];

        glBegin(GL_TRIANGLES);

        for (GLuint j = 0; j < mesh->mNumFaces; j++)
        {
            aiFace face = mesh->mFaces[j];
            for (GLuint k = 0; k < face.mNumIndices; k++)
            {

                GLuint vertexIndex = face.mIndices[k];

                aiVector3D vertex = mesh->mVertices[vertexIndex];
                aiVector3D normal = mesh->mNormals[vertexIndex];

                aiVector3D textureCoords = mesh->mTextureCoords[0][vertexIndex];

                glTexCoord2f(textureCoords.x, textureCoords.y);

                glNormal3f(normal.x, normal.y, normal.z);

                glm::vec3 newColor =
                    Light::getInstance()
                        ->lighting(
                            Point(vertex.x, vertex.y, vertex.z),                            // ponto
                            Point(cameraPosition->x, cameraPosition->y, cameraPosition->z), // camera
                            this->ambientComponents->ambient,                               // ambient material
                            this->ambientComponents->diffuse,                               // diffuse material
                            this->ambientComponents->specular,                              // specular material
                            this->ambientComponents->shine,                                 // shine material
                            glm::vec3(normal.x, normal.y, normal.z)                         // normal
                        );

                glColor3f(newColor.r, newColor.g, newColor.b);
                glVertex3f(
                    vertex.x * 1,
                    vertex.y * 1,
                    vertex.z * 1);
            }
        }

        glEnd();
    }
}

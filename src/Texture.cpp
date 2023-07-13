#include "../include/texture.h"

void Texture::load(std::string path)
{
	this->texture = SOIL_load_OGL_texture(
		path.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);

	if (texture == 0)
	{
		std::cout << "Path: " << path << std::endl
				  << "Texture error:" << SOIL_last_result() << std::endl;
	}
}

GLuint Texture::getTexture()
{
	return this->texture;
}

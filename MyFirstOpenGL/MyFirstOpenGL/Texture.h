#pragma once
#include <iostream>
#include "stb_image.h"
#include <GL/glew.h> 


class Texture
{
public:

	Texture() = default;
	void InitializeTexture(const char* filePath, GLenum textureUnit);
	GLuint textureID;
};


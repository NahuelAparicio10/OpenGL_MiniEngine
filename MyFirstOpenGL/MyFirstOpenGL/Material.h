#pragma once
#include "ProgramManager.h"

class Material
{
public:
	
	Material();
	void LoadMaterial(const std::string& filePath);
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 emissive;
	float opacity;

};


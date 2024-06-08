#pragma once
#include "Model.h"
#include <vector>
#include <sstream>
#include <glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	void GenerateModels();
	const std::vector<Model*>& GetModels() const { return models; };
	Model* GetModelByType(ModelType type);

private:
	Model* LoadOBJModel(int IDProgram, const std::string& filePath, const char* texturefilePath, const std::string& matFilePath, GLenum textureUnit, ModelType type);
	std::vector<Model*> models;

};


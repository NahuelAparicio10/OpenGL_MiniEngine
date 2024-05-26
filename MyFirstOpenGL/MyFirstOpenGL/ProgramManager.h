#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stb_image.h>




struct ShaderProgram {
	GLuint vertexShader = 0;
	GLuint geometryShader = 0;
	GLuint fragmentShader = 0;
};
class ProgramManager
{
public:
	static ProgramManager& getInstance() {static ProgramManager instance;return instance;}
	ProgramManager();
	GLuint CreateProgram(const ShaderProgram& shaders);
	GLuint LoadVertexShader(const std::string& filePath);
	GLuint LoadGeometryShader(const std::string& filePath);
	GLuint LoadFragmentShader(const std::string& filePath);
	std::string Load_File(const std::string& filePath);
	glm::mat4 GenerateScaleMatrix(glm::vec3 scaleAxis);
	glm::mat4 GenerateRotationMatrix(glm::vec3 axis, float fDegrees);
	glm::mat4 GenerateTranslationMatrix(glm::vec3 translation);

	ShaderProgram * myFirstProgram;
	ShaderProgram * mySecondProgram;
	ShaderProgram * myThirdProgram;
	ShaderProgram * myFourthProgram;
	ShaderProgram * myFifthProgram;
	std::vector<GLuint> compiledPrograms;

private:
	ProgramManager(const ProgramManager&) = delete;
	ProgramManager& operator=(const ProgramManager&) = delete;
};

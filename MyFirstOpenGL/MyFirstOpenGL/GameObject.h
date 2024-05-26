#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class GameObject
{

public:
	GameObject() = default;
	GameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 localVectorUp){}


	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;
	glm::vec3 _localVectorUp;
	glm::vec3 _vectorFront;
	glm::vec3 _direction;


};




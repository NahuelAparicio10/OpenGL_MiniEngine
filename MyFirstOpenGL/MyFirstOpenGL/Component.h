#pragma once
#include <typeindex>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>

class Component
{
public:
	Component() = default;
	virtual ~Component() = default;

	virtual const std::type_index GetType() = 0;
};

#pragma once

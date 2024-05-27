#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "Primitive.h"
#include "Camera.h"


struct Mouse
{
	float yaw;
	float pitch;
	float lastPositionX;
	float lastPositionY;
	bool firstMouse;

	Mouse() : yaw(-90.0f), pitch(0.0f), lastPositionX(400), lastPositionY(300), firstMouse(true) {}

	void setYaw(float _yaw) { yaw = _yaw; }
	void setPitch(float _pitch) { pitch = _pitch; }
	void setLastPositionX(float _lastPositionX) { lastPositionX = _lastPositionX; }
	void setLastPositionY(float _lastPositionY) { lastPositionY = _lastPositionY; }
	void setFirstMouse(bool _firstMouse) { firstMouse = _firstMouse; }

	void setMouseDirection(GLFWwindow* window, float xpos, float ypos)
	{
		if (firstMouse)
		{
			lastPositionX = xpos;
			lastPositionY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastPositionX;
		float yoffset = lastPositionY - ypos;
		lastPositionX = xpos;
		lastPositionY = ypos;

		float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		Camera::getInstance().setVectorFront(glm::normalize(direction));
	}


};

class InputManager
{
public:
	InputManager();
	void HandleInputs(GLFWwindow* window);

	// Getters
	Mouse* getMouse() { return mouse; };

	bool IsWPressed() { return wPressed; }
	bool IsAPressed() { return aPressed; }
	bool IsSPressed() { return sPressed; }
	bool IsDPressed() { return dPressed; }

	// Setters

private:
	Mouse* mouse;
	void UpdateInputs(GLFWwindow* window);
	void UpdateMouse(GLFWwindow* window);

	bool wPressed;
	bool aPressed;
	bool sPressed;
	bool dPressed;
};



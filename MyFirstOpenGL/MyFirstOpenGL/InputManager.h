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
	glm::vec3 mouseDir;

	Mouse() : yaw(-90.0f), pitch(0.0f), lastPositionX(400), lastPositionY(300), firstMouse(true), mouseDir({0,0,0}) {}

	void SetYaw(float _yaw) { yaw = _yaw; }
	void SetPitch(float _pitch) { pitch = _pitch; }
	void SetLastPositionX(float _lastPositionX) { lastPositionX = _lastPositionX; }
	void SetLastPositionY(float _lastPositionY) { lastPositionY = _lastPositionY; }
	void SetFirstMouse(bool _firstMouse) { firstMouse = _firstMouse; }

	void SetMouseDirection(GLFWwindow* window, float xpos, float ypos)
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
		mouseDir = glm::normalize(direction);
	}
};

class InputManager
{
public:
	InputManager();
	void HandleInputs(GLFWwindow* window);

	// Getters
	Mouse* GetMouse() { return mouse; };
	bool IsWPressed() { return _wPressed; }
	bool IsAPressed() { return _aPressed; }
	bool IsSPressed() { return _sPressed; }
	bool IsDPressed() { return _dPressed; }
	bool IsFPressed() { return _fPressed; }
	bool WasFPressed() { return _wasFPressed; }
	// Setters

private:
	Mouse* mouse;
	void UpdateInputs(GLFWwindow* window);
	void UpdateMouse(GLFWwindow* window);

	bool _wPressed;
	bool _aPressed;
	bool _sPressed;
	bool _dPressed;
	bool _fPressed;
	bool _wasFPressed;
};



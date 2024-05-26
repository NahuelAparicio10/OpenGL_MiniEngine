#include "InputManager.h"

InputManager::InputManager()
{
	mouse = new Mouse();
	wPressed = false;
	aPressed = false;
	sPressed = false;
	dPressed = false;

}

void InputManager::HandleInputs(GLFWwindow* window)
{
	UpdateInputs(window);
	UpdateMouse(window);
}

void InputManager::UpdateInputs(GLFWwindow* window)
{
	wPressed = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
	aPressed = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
	sPressed = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
	dPressed = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
}

void InputManager::UpdateMouse(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	getMouse()->setMouseDirection(window, xpos, ypos);
}

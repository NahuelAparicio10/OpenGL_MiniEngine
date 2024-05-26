#include "TimeManager.h"


TimeManager::TimeManager() : deltaTime(0)
{
	lastFrameTime = static_cast<float>(glfwGetTime());
}

void TimeManager::HandleTime()
{
	float currentFrameTime = static_cast<float>(glfwGetTime());
	deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;
}

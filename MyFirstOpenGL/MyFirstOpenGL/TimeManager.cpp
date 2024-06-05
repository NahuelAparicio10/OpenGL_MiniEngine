#include "TimeManager.h"
#include <iostream>


TimeManager::TimeManager() : _deltaTime(0)
{
	_lastFrameTime = static_cast<float>(glfwGetTime());
	_elapsedTime = 0;
	_cycleDuration = 40.f; // how many seconds for complete the day/night Cycle
}

void TimeManager::HandleTime()
{
	float currentFrameTime = static_cast<float>(glfwGetTime());
	_deltaTime = currentFrameTime - _lastFrameTime;
	_lastFrameTime = currentFrameTime;
	_elapsedTime += _deltaTime;
}

float TimeManager::CalculateTimeOfDay() const
{
	float normalizedTime = fmod(_elapsedTime, _cycleDuration);
	return normalizedTime / _cycleDuration;
}

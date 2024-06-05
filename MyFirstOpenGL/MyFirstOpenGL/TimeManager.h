#pragma once
#include <GLFW/glfw3.h>
class TimeManager
{
public:
	TimeManager();
	void HandleTime();
	float CalculateTimeOfDay() const;


	float GetDeltaTime() { return _deltaTime; };
	float GetElapsedTime() { return _elapsedTime; };

private:
	float _cycleDuration;

	float _deltaTime;
	float _lastFrameTime;
	float _elapsedTime;
};


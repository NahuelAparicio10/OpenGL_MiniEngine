#pragma once
#include <GLFW/glfw3.h>
class TimeManager
{
public:
	TimeManager();
	void HandleTime();

	float GetDeltaTime() { return deltaTime; };

private:
	float deltaTime;
	float lastFrameTime;
};


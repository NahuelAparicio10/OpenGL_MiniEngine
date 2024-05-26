#pragma once
#include <GLFW/glfw3.h>
class TimeManager
{
public:
	TimeManager();
	void HandleTime();

	float getDeltaTime() { return deltaTime; };

private:
	float deltaTime;
	float lastFrameTime;
};


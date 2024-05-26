#pragma once
#include "Model.h"
#include "InputManager.h"
#include "TimeManager.h"

class Engine
{
public:
	//Singleton to call from everywhere
	static Engine& getInstance() { static Engine instance; return instance; }
	Engine();

	//Functions utils
	void Init();
	void Update(GLFWwindow* window);
	Model* LoadOBJModel(int IDProgram, const std::string& filePath, const char* texturefilePath, const std::string& matFilePath,GLenum textureUnit, ModelType type);

	//Getters
	InputManager* getInputManager() { return inputManager; };
	TimeManager* getTimeManager() { return timeManager; };
	
private:
	InputManager* inputManager;
	TimeManager* timeManager;

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
};


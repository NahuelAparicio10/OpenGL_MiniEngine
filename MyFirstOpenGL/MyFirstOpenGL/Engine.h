#pragma once
#include "Model.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ModelManager.h"
#include "MapManager.h"
#include "ObjectsManager.h"
#include "SpotLight.h"

class Engine
{
public:
	static Engine& GetInstance() { static Engine instance; return instance; }
	Engine();

	void Init();
	void Update(GLFWwindow* window);
	void Render();
	
	//Getters
	InputManager* GetInputManager() { return _inputManager; };
	TimeManager* GetTimeManager() { return _timeManager; };
	ModelManager* GetModelManager() { return _modelManager; };
	MapManager* GetMapManager() { return _mapManager; };
	ObjectsManager* GetObjectsManager() { return _objectsManager; };
	
private:
	InputManager* _inputManager;
	TimeManager* _timeManager;
	ModelManager* _modelManager;
	MapManager* _mapManager;
	ObjectsManager* _objectsManager;

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
};


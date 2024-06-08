#include "Engine.h"

Engine::Engine()
{ 
	_inputManager = new InputManager();
	_timeManager = new TimeManager();
	_modelManager = new ModelManager();
	_mapManager = new MapManager();

	GameObject* sun = new GameObject();
	sun->AddComponent<MeshRenderer>(new Model(*_modelManager->GetModelByType(ModelType::Sun)), sun);
	GameObject* moon = new GameObject();
	moon->AddComponent<MeshRenderer>(new Model(*_modelManager->GetModelByType(ModelType::Moon)), moon);
	_objectsManager = new ObjectsManager(sun, moon);
}

void Engine::Init()
{
	_mapManager->InitializeMap();
}

void Engine::Update(GLFWwindow* window)
{
	_timeManager->HandleTime();

	_objectsManager->UpdateObjects();

	_inputManager->HandleInputs(window);

	_objectsManager->GetCamera()->SetVectorFront(_inputManager->GetMouse()->mouseDir);

	_objectsManager->GetCamera()->Update(window);

}

void Engine::Render()
{
	//Static Objects
	_mapManager->RenderMapObjects(_objectsManager->GetCamera()->GetViewMatrix());

	//Dynamic Objects
	_objectsManager->RenderObjects(_objectsManager->GetCamera()->GetViewMatrix());
}











#include "Engine.h"

Engine::Engine()
{
}

void Engine::Init()
{
	_inputManager = new InputManager();
	_timeManager = new TimeManager();
	_modelManager = new ModelManager();
	GenerateGameObjects();
}

void Engine::Update(GLFWwindow* window)
{
	_timeManager->HandleTime();

	_inputManager->HandleInputs(window);

	Camera::getInstance().Update(window);
}

void Engine::Render(glm::mat4 view)
{
	for (MeshRenderer* gameObject : gameObjects)
	{
		gameObject->Render(view);
	}
}

void Engine::GenerateGameObjects()
{
	MeshRenderer* lanscape = new MeshRenderer(new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Landscape)));
	lanscape->_position = glm::vec3{ 0.f,0.f,0.f };
	lanscape->_rotation = glm::vec3{ 0.f,0.f,0.f };
	lanscape->_scale = glm::vec3{ 1.f,1.f,1.f };

	gameObjects.push_back(lanscape);

	MeshRenderer* rock1 = new MeshRenderer(new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Rock)));
	rock1->_position = glm::vec3{ 5.f,0.f,5.f };
	rock1->_rotation = glm::vec3{ 0.f,0.f,0.f };
	rock1->_scale = glm::vec3{ 1.f,1.f,1.f };
	MeshRenderer* rock2 = new MeshRenderer(new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Rock)));
	rock2->_position = glm::vec3{ 25.f,0.f,25.f };
	rock2->_rotation = glm::vec3{ 0.f,0.f,0.f };
	rock2->_scale = glm::vec3{ 1.f,1.f,1.f };
	MeshRenderer* rock3 = new MeshRenderer(new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Rock)));
	rock3->_position = glm::vec3{ -15.f,0.f,-15.f };
	rock3->_rotation = glm::vec3{ 0.f,0.f,0.f };
	rock3->_scale = glm::vec3{ 1.f,1.f,1.f };
	MeshRenderer* rock4 = new MeshRenderer(new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Rock)));
	rock4->_position = glm::vec3{ 7.f,0.f,7.f };
	rock4->_rotation = glm::vec3{ 0.f,0.f,0.f };
	rock4->_scale = glm::vec3{ 1.f,1.f,1.f };

	gameObjects.push_back(rock1);
	gameObjects.push_back(rock2);
	gameObjects.push_back(rock3);
	gameObjects.push_back(rock4);
	//rock1 = Engine::getInstance().LoadOBJModel(0, "Assets/Models/rock.obj", "Assets/Textures/rock/rock_bc.png", "Assets/Materials/rock.mtl",GL_TEXTURE0, ModelType::Rock);
	//models.push_back(rock1);
}











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
	for (GameObject* gameObject : gameObjects)
	{
		gameObject->GetComponent<MeshRenderer>()->Render(view);
	}
}

void Engine::GenerateGameObjects()
{
	GameObject* lanscape = new GameObject();
	//new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Landscape))
	lanscape->AddComponent<MeshRenderer>(new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Landscape)),lanscape);
	Transform* transform = lanscape->GetComponent<Transform>();

	transform->_position = glm::vec3{ 0.f,0.f,0.f };
	transform->_rotation = glm::vec3{ 0.f,0.f,0.f };
	transform->_scale = glm::vec3{ 1.f,1.f,1.f };

	gameObjects.push_back(lanscape);

	GameObject* rock1 = new GameObject();
	rock1->AddComponent<MeshRenderer>(new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Rock)), rock1);
	rock1->GetComponent<Transform>()->_position = glm::vec3{ 5.f,0.f,5.f };


	GameObject* rock2 = new GameObject();
	rock2->AddComponent<MeshRenderer>(new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Rock)), rock2);
	rock2->GetComponent<Transform>()->_position = glm::vec3{ -1000.f,0.f,-1000.f };

	GameObject* rock3 = new GameObject();
	rock3->AddComponent<MeshRenderer>(new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Rock)), rock3);
	rock3->GetComponent<Transform>()->_position = glm::vec3{ 1000.f,0.f,1000.f };


	gameObjects.push_back(rock1);
	gameObjects.push_back(rock2);
	gameObjects.push_back(rock3);

	//MeshRenderer* rock1 = new MeshRenderer(new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Rock)));
	//rock1->_position = glm::vec3{ 5.f,0.f,5.f };
	//rock1->_rotation = glm::vec3{ 0.f,0.f,0.f };
	//rock1->_scale = glm::vec3{ 1.f,1.f,1.f };
	//MeshRenderer* rock2 = new MeshRenderer(new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Rock)));
	//rock2->_position = glm::vec3{ 25.f,0.f,25.f };
	//rock2->_rotation = glm::vec3{ 0.f,0.f,0.f };
	//rock2->_scale = glm::vec3{ 1.f,1.f,1.f };
	//MeshRenderer* rock3 = new MeshRenderer(new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Rock)));
	//rock3->_position = glm::vec3{ -15.f,0.f,-15.f };
	//rock3->_rotation = glm::vec3{ 0.f,0.f,0.f };
	//rock3->_scale = glm::vec3{ 1.f,1.f,1.f };
	//MeshRenderer* rock4 = new MeshRenderer(new Model(*Engine::getInstance().GetModelManager()->GetModelByType(ModelType::Rock)));
	//rock4->_position = glm::vec3{ 7.f,0.f,7.f };
	//rock4->_rotation = glm::vec3{ 0.f,0.f,0.f };
	//rock4->_scale = glm::vec3{ 1.f,1.f,1.f };

	//gameObjects.push_back(rock1);
	//gameObjects.push_back(rock2);
	//gameObjects.push_back(rock3);
	//gameObjects.push_back(rock4);
	//rock1 = Engine::getInstance().LoadOBJModel(0, "Assets/Models/rock.obj", "Assets/Textures/rock/rock_bc.png", "Assets/Materials/rock.mtl",GL_TEXTURE0, ModelType::Rock);
	//models.push_back(rock1);
}











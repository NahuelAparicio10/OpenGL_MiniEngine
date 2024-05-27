#include "MapManager.h"
#include "Engine.h"
MapManager::MapManager()
{
	_numOfObjects = 16;
	spawnPoints.push_back({ 0, 0, 0 });
	spawnPoints.push_back({ 50, 0, 50 });
	spawnPoints.push_back({ 50, 0, -50 });
	spawnPoints.push_back({ -50, 0, 50 });
	spawnPoints.push_back({ 25, 0, 25 });
	spawnPoints.push_back({ -25, 0, 25 });
}

void MapManager::InitializeMap()
{
	GameObject* lanscape = new GameObject();
	lanscape->AddComponent<MeshRenderer>(new Model(*Engine::GetInstance().GetModelManager()->GetModelByType(ModelType::Terrain)), lanscape);
	Transform* transform = lanscape->GetComponent<Transform>();
	transform->_scale = { 0.05, 0.05, 0.05 };

	gameObjects.push_back(lanscape);


	GenerateGameObject(ModelType::Rock);

	GenerateGameObject(ModelType::Bush);

	GenerateGameObject(ModelType::Tree);
}

void MapManager::GenerateGameObject(ModelType type)
{
	for (int i = 0; i < _numOfObjects; i++)
	{
		GameObject* go = new GameObject();
		go->AddComponent<MeshRenderer>(new Model(*Engine::GetInstance().GetModelManager()->GetModelByType(type)), go);
		SetObjectsTransform(go->GetComponent<Transform>());
		gameObjects.push_back(go);
	}
}

void MapManager::SetObjectsTransform(Transform* transform)
{
	if (!spawnPoints.empty())
	{
		transform->_position = Utils::GetUniquePosition(spawnPoints);
	}
	else
	{
		transform->_position = glm::vec3{ Utils::RandomRange(-50.f, 50.f), 0, Utils::RandomRange(-50.f, 50.f) };
	}
	float randomScale = Utils::RandomRange(0.5f, 1.5f);
	transform->_scale = { randomScale, randomScale, randomScale };
	transform->_rotation = { Utils::RandomRange(0, 5), Utils::RandomRange(0, 360), Utils::RandomRange(0, 5) };
}

void MapManager::RenderMapObjects(glm::mat4 view)
{
	for (GameObject* gameObject : gameObjects)
	{
		gameObject->GetComponent<MeshRenderer>()->Render(view);
	}
}
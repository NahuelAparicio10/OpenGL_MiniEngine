#include "MapManager.h"
#include "Engine.h"

MapManager::MapManager()
{
	_numOfObjects = 4;
	_numOfGrass = 50;
	spawnPoints.push_back({ 0, 0, 0 });
	spawnPoints.push_back({ 50, 0, 50 });
	spawnPoints.push_back({ 50, 0, -50 });
	spawnPoints.push_back({ -50, 0, 50 });
	spawnPoints.push_back({ 25, 0, 25 });
	spawnPoints.push_back({ -25, 0, 25 });

	gradientColors = LoadGradientColors("Assets/Textures/Colores.png");
}

void MapManager::InitializeMap()
{
	GameObject* lanscape = new GameObject();
	lanscape->AddComponent<MeshRenderer>(new Model(*Engine::GetInstance().GetModelManager()->GetModelByType(ModelType::Terrain)), lanscape);
	Transform* transform = lanscape->GetComponent<Transform>();
	transform->_scale = { 0.05, 0.05, 0.05 };

	gameObjects.push_back(lanscape);

	// This will generate as many as _numOfObjects for each Obj
	GenerateGameObject(ModelType::Rock, _numOfObjects);

	GenerateGameObject(ModelType::Bush, _numOfObjects);

	GenerateGameObject(ModelType::Tree, _numOfObjects);

	GenerateGameObject(ModelType::Grass, _numOfGrass);

}

void MapManager::GenerateGameObject(ModelType type, int numToGenerate)
{
	for (int i = 0; i < numToGenerate; i++)
	{
		GameObject* go = new GameObject();
		go->AddComponent<MeshRenderer>(new Model(*Engine::GetInstance().GetModelManager()->GetModelByType(type)), go);
		SetObjectsTransform(go->GetComponent<Transform>());
		if (type == ModelType::Grass)
		{
			SetRandomScale(go->GetComponent<Transform>(), 2, 3);
		}
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
	SetRandomScale(transform, 0.5f, 1.5f);
	transform->_rotation = { Utils::RandomRange(0, 5), Utils::RandomRange(0, 360), Utils::RandomRange(0, 5) };
}

void MapManager::SetRandomScale(Transform* transform, float minScale, float maxScale)
{
	float randomScale = Utils::RandomRange(minScale, maxScale);
	transform->_scale = { randomScale, randomScale, randomScale };
}

// -- Renders all the static objects of the map

void MapManager::RenderMapObjects(glm::mat4 view)
{
	for (GameObject* gameObject : gameObjects)
	{
		gameObject->GetComponent<MeshRenderer>()->Render(view);
	}
}

// -- Given a filepath returns a vector of colors like a gradient, which we will use for interpolate between them after.
// Each row in the image represents a color

std::vector<glm::vec3> MapManager::LoadGradientColors(const char* filepath) {
	int width, height, channels;
	unsigned char* data = stbi_load(filepath, &width, &height, &channels, 0);

	if (!data) {
		std::cerr << "Failed to load texture" << std::endl;
		return {};
	}

	std::vector<glm::vec3> colors(width);

	// gets the colors of the textures by x axis 
	for (int x = 0; x < width; ++x) {
		int index = x * channels;
		glm::vec3 color(data[index] / 255.0f, data[index + 1] / 255.0f, data[index + 2] / 255.0f);
		colors[x] = color;
	}

	stbi_image_free(data);
	return colors;
}

// -- Returns the color depending on the time of the day, given a color's gradient

glm::vec3 MapManager::GetInterpolatedColor(float timeOfDay) {

	float scaledTime = timeOfDay * (gradientColors.size() - 1);
	int index1 = static_cast<int>(scaledTime);
	int index2 = (index1 + 1) % gradientColors.size();
	float t = scaledTime - index1;

	return glm::mix(gradientColors[index1], gradientColors[index2], t);
}

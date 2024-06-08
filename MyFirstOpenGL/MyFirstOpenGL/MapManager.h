#pragma once
#include <vector>
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Utils.h"

// -- Stores Static Game Objects (that won't move in play mode)
class MapManager
{
public:
	MapManager();
	void InitializeMap();
	void RenderMapObjects(glm::mat4 view);
	glm::vec3 GetInterpolatedColor(float timeOfDay);
private:
	std::vector<glm::vec3> LoadGradientColors(const char* filepath);
	void SetObjectsTransform(Transform* transform);
	void SetRandomScale(Transform* transform, float minScale, float maxScale);
	void GenerateGameObject(ModelType type, int numToGenerate);
	std::vector<GameObject*> gameObjects;
	std::vector<glm::vec3> spawnPoints; // Predefined spawn points, if there's no spawn point created will spawn Random
	int _numOfObjects; // The number of each object that will spawn.
	int _numOfGrass;
	std::vector<glm::vec3> gradientColors;
};
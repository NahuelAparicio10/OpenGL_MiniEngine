#pragma once
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Lantern.h"

// -- Manages the Dynamic GameObjects

class ObjectsManager
{
public:
	ObjectsManager(GameObject* sun, GameObject* moon);
	void UpdateObjects();
	void RenderObjects(glm::mat4 view);
	void UpdateOrbit(GameObject* object, float elapsedTime);

	GameObject* GetSun() { return _sun; }
	GameObject* GetMoon() { return _moon; }
	Camera* GetCamera() { return _camera; }
	Lantern* GetLantern() { return _lantern; }

private:
	GameObject* _sun;
	GameObject* _moon;
	Camera* _camera;
	Lantern* _lantern;
	float _angularSpeed;
};


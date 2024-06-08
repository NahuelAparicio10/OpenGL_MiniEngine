#pragma once
#include "GameObject.h"
#include "SpotLight.h"

class Lantern : public GameObject
{
public:
	Lantern();
	void UpdateLantern(glm::vec3 pos, glm::vec3 frontVec);
	bool IsLanternEnabled() { return _lanternEnabled; }
	SpotLight* GetSpotLight() { return _spotLight; }
	Transform* GetTransform() { return _transform; }
private:
	bool _lanternEnabled;
	Transform* _transform;
	SpotLight* _spotLight;
};


#pragma once
#include "Component.h"
#include "GameObject.h"

class SpotLight : public Component
{
public:
	SpotLight(GameObject* owner);
	const std::type_index GetType() override;

	void SetInnerCutOff(float v) { _innerCutOff = v; }
	void SetOutterCutOff(float v) { _outerCutOff = v; }
	void SetMaxDistance(float v) { _maxDistance = v; }
	void SetLightIntensity(float v) { _lightIntensity = v; }
	void SetLightColor(glm::vec3 color) { _lightColor = color; }

	float GetInnerCutOff() { return _innerCutOff; }
	float GetOutterCutOff() { return _outerCutOff; }
	float GetMaxDistance() { return _maxDistance; }
	float GetLightIntensity() { return _lightIntensity; }
	glm::vec3 GetLightColor() { return _lightColor; }

private:
	GameObject* _owner;
	float _innerCutOff;
	float _outerCutOff;
	float _maxDistance;
	float _lightIntensity;
	glm::vec3 _lightColor;
};


#pragma once
#include "Model.h"
#include "Material.h"
#include "Component.h"
#include "Camera.h"


class MeshRenderer : public Component
{
public:
	MeshRenderer(Model* model, GameObject* owner);
	void Render(glm::mat4 view);
	const std::type_index GetType() override;

private:
	glm::vec3 CalculateLightDirection(float angleSun, glm::vec3 sunDirection, glm::vec3 moonDirection);
	float GetLightFactor(float angleSun);
	GameObject* _owner;
	Model* _model;
	Transform* _transform;
	float _ambientIntensity;
	glm::vec3 _ambientSun;
	glm::vec3 _ambientMoon;

};


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
	GameObject* _owner;
	Model* _model;
	Transform* _transform;
};


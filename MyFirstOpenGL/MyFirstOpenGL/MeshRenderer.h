#pragma once
#include "Model.h"
#include "Material.h"
#include "GameObject.h"
#include "Camera.h"

class MeshRenderer : public GameObject
{
public:
	MeshRenderer(Model* model);
	void Render(glm::mat4 view);

private:
	Model* _model;
};


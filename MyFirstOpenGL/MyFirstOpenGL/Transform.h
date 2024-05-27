#pragma once
#include "GameObject.h"
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	const std::type_index GetType() override;

	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;

	glm::vec3 _localVectorUp;
	glm::vec3 _vectorFront;
	glm::vec3 _direction;

private:
};


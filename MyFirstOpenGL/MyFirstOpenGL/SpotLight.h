#pragma once
#include "Component.h"
#include "Camera.h"

class SpotLight : public Component
{
public:
	SpotLight();
	void ProjectLight();
	const std::type_index GetType() override;

private:
	GLfloat _cutOff ;
	GLfloat _exponent;
};


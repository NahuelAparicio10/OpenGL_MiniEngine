#include "SpotLight.h"

SpotLight::SpotLight(GameObject* owner) : _owner(owner)
{
	_innerCutOff = 0;
	_outerCutOff = 0;
	_maxDistance = 0;
	_lightIntensity = 0;
	_lightColor = glm::vec3(0.0);
}

const std::type_index SpotLight::GetType()
{
	return typeid(SpotLight);
}
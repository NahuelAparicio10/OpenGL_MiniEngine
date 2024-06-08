#include "Lantern.h"
#include "Engine.h"

Lantern::Lantern()
{
	AddComponent<SpotLight>(this);
	_transform = GetComponent<Transform>();
	_spotLight = GetComponent<SpotLight>();
	_lanternEnabled = false;

	_spotLight->SetInnerCutOff(10.0f);
	_spotLight->SetOutterCutOff(20.0f);
	_spotLight->SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_spotLight->SetMaxDistance(100.0f);
	_spotLight->SetLightIntensity(1.0f);

	_transform->_rotation = { 0.f, 0.f, 0.f };
	_transform->_localVectorUp = { 0.f, 1.f, 0.f };
	_transform->_vectorFront = { 0.f, 0.f, 1.f };
}

//Update Lanterns Position by a given pos

void Lantern::UpdateLantern(glm::vec3 pos, glm::vec3 frontVec)
{
	if (Engine::GetInstance().GetInputManager()->IsFPressed())
	{
		_lanternEnabled = !_lanternEnabled;
	}

	if (_lanternEnabled)
	{
		_transform->_position = pos;
		_transform->_vectorFront = frontVec;
	}
}

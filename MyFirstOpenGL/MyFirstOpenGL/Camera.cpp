#include "Camera.h"
#include "Engine.h"

Camera::Camera() : _fFov(45.0f), _aspectRatio(1.0), _fNear(0.1), _fFar(20000.0),_speed(200)
{
	_position = { 0.f,2.f,-5.f };
	_rotation = { 0.f,0.f,0.f };
	_localVectorUp = { 0.f,1.f,0.f };
	_vectorFront = { 0.f,0.f,1.f };
}

void Camera::Update(GLFWwindow* window)
{
	//Inputs logic function, we do the keyoard and mouse updates
	UpdateCamPosition(window);
	//Function that does the camera view function 
	LookAt();

}

void Camera::LookAt()
{
	_viewMatrix = glm::lookAt(_position, _position + _vectorFront, _localVectorUp);
	MatrixView(_viewMatrix);
}

void Camera::UpdateCamPosition(GLFWwindow* window)
{
	float tempMultiplier = _speed * Engine::getInstance().getTimeManager()->getDeltaTime();
	if (Engine::getInstance().getInputManager()->IsWPressed())
	{
		_position += tempMultiplier * _vectorFront;
	}
	if (Engine::getInstance().getInputManager()->IsSPressed())
	{
		_position -= tempMultiplier *_vectorFront;
	}
	if (Engine::getInstance().getInputManager()->IsAPressed())
	{
		_position -= glm::normalize(glm::cross(_vectorFront, _localVectorUp)) * tempMultiplier;
	}
	if (Engine::getInstance().getInputManager()->IsDPressed())
	{
		_position += glm::normalize(glm::cross(_vectorFront, _localVectorUp)) * tempMultiplier;
	}
}

glm::mat4 Camera::MatrixView(glm::mat4 viewMat)
{
	return viewMat;
}

#include "Camera.h"
#include "Engine.h"

Camera::Camera() : _fFov(45.0f), _aspectRatio(1.0), _fNear(0.1), _fFar(20000.0),_speed(200)
{
	_transform = GetComponent<Transform>();
	_transform->_position = { 0.f,2.f,-5.f };
	_transform->_rotation = { 0.f,0.f,0.f };
	_transform->_localVectorUp = { 0.f,1.f,0.f };
	_transform->_vectorFront = { 0.f,0.f,1.f };
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
	_viewMatrix = glm::lookAt(_transform->_position, _transform->_position + _transform->_vectorFront, _transform->_localVectorUp);
	MatrixView(_viewMatrix);
}

void Camera::UpdateCamPosition(GLFWwindow* window)
{
	float tempMultiplier = _speed * Engine::GetInstance().GetTimeManager()->GetDeltaTime();
	if (Engine::GetInstance().getInputManager()->IsWPressed())
	{
		_transform->_position += tempMultiplier * _transform->_vectorFront;
	}
	if (Engine::GetInstance().getInputManager()->IsSPressed())
	{
		_transform->_position -= tempMultiplier * _transform->_vectorFront;
	}
	if (Engine::GetInstance().getInputManager()->IsAPressed())
	{
		_transform->_position -= glm::normalize(glm::cross(_transform->_vectorFront, _transform->_localVectorUp) * tempMultiplier);
	}
	if (Engine::GetInstance().getInputManager()->IsDPressed())
	{
		_transform->_position += glm::normalize(glm::cross(_transform->_vectorFront, _transform->_localVectorUp) * tempMultiplier);
	}
}

glm::mat4 Camera::MatrixView(glm::mat4 viewMat)
{
	return viewMat;
}

#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera();

	//Getters
	float GetfFov() const { return _fFov; }
	float GetAspectRatio() const { return _aspectRatio; }
	float GetfNear() const { return _fNear; }
	float GetfFar() const { return _fFar; }
	float GetXPos() const { return _transform->_position.x; }
	float GetYPos() const { return _transform->_position.y; }
	glm::vec3 GetPosition() const { return _transform->_position; };
	glm::vec3 GetVectorFront() const { return _transform->_vectorFront; }	
	glm::mat4 GetViewMatrix() const { return _viewMatrix; }
	

	//Setters
	void setfFov(float fFov) { _fFov = fFov; }
	void setaspectRatio(float aspectRatio) { _aspectRatio = aspectRatio; }
	void setfNear(float fNear) { _fNear = fNear; }
	void set_fFar(float fFar) { _fFar = fFar; }
	void setXPos(float xPos) { _transform->_position.x = xPos; }
	void setYPos(float yPos) { _transform->_position.y = yPos; }
	void SetVectorFront(glm::vec3 vFront) { _transform->_vectorFront = vFront; }

	void Update(GLFWwindow* window);
	glm::mat4 MatrixView(glm::mat4 viewMat);

private:
	void UpdateCamPosition(GLFWwindow* window);
	void LookAt();

	float _fFov;
	float _aspectRatio;
	float _fNear;
	float _fFar;
	const float _speed;
	
	glm::mat4 _viewMatrix;
	Transform* _transform;	
};




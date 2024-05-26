#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>

class Primitive
{
private:
    bool _isRendering;
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;
    glm::vec3 _forward;
    float _yVelocity;
    float _zVelocity;
    float _fScaleVelocity;
    float _fAngularVelocity;

public:
    // Getters
    bool isRendering() const { return _isRendering; }
    glm::vec3 getPosition() const { return _position; }
    glm::vec3 getPositionY() const { return _position; }
    glm::vec3 getRotation() const { return _rotation; }
    glm::vec3 getScale() const { return _scale; }
    glm::vec3 getForward() const { return _forward; }
    float getYVelocity() const { return _yVelocity; }
    float getZVelocity() const { return _zVelocity; }
    float getFScaleVelocity() const { return _fScaleVelocity; }
    float getFAngularVelocity() const { return _fAngularVelocity; }

    // Setters
    void setIsRendering(bool isRendering) { _isRendering = isRendering; }
    void setPosition(const glm::vec3& position) { _position = position; }
    void setRotation(const glm::vec3& rotation) { _rotation = rotation; }
    void setScale(const glm::vec3& scale) { _scale = scale; }
    void setForward(const glm::vec3& forward) { _forward = forward; }
    void setYVelocity(float yVelocity) { _yVelocity = yVelocity; }
    void setZVelocity(float zVelocity) { _zVelocity = zVelocity; }
    void setFScaleVelocity(float fScaleVelocity) { _fScaleVelocity = fScaleVelocity; }
    void setFAngularVelocity(float fAngularVelocity) { _fAngularVelocity = fAngularVelocity; }

    // Constructor
    Primitive()
        : _isRendering(true),
        _position(0.f),
        _rotation(0.f),
        _scale(1.f),
        _forward(0.f, 1.f, 0.f),
        _yVelocity(0.1f),
        _zVelocity(0.01f),
        _fScaleVelocity(0.1f),
        _fAngularVelocity(-5.f)
    {
    }

};


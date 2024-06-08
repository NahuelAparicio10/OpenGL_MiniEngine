#include "Transform.h"

Transform::Transform()
{
    _position = glm::vec3(0, 0, 0);
    _rotation = glm::vec3(0, 0, 0);
    _scale = glm::vec3(1, 1, 1);

    _localVectorUp = glm::vec3(0, 0, 0);
    _vectorFront = glm::vec3(0, 0, 0);
    _direction = glm::vec3(0, 0, 0);
}

const std::type_index Transform::GetType()
{
    return typeid(Transform);
}




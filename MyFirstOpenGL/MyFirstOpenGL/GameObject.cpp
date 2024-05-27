#include "GameObject.h"

GameObject::GameObject()
{
    AddComponent<Transform>();
}

GameObject::~GameObject()
{
    for (Component* component : components)
    {
        delete component;
    }
}


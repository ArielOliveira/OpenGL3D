#include "Object.hpp"

Object::Object() : Entity() {}

Object::Object(const Object& object) : 
    Entity(object),
    components(object.components)
    {}

Object::~Object() {
    Entity::~Entity();
}

void Object::step(float deltaTime) {
    computeModelMtx();
}


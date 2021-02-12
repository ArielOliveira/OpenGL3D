#include "Entity.h"

Entity::Entity() :
	pos(glm::vec3(0)),
	rot(glm::vec3(0)),
	size(glm::vec3(0)),
	modelMtx(glm::mat4(1))
{}

Entity::Entity(const Entity& entity) : 
	pos(entity.pos),
	rot(entity.rot),
	size(entity.size),
	modelMtx(entity.modelMtx) 
{}

Entity::~Entity() {}

void Entity::setPos(glm::vec3 pos) { this->pos = pos; }
glm::vec3 Entity::getPos() { return pos; }

void Entity::setRot(glm::vec3 rot) { this->rot = rot; }
glm::vec3 Entity::getRot() { return rot; }

void Entity::setSize(glm::vec3 size) { this->size = size; }
glm::vec3 Entity::getSize() { return size; }

void Entity::computeModelMtx() {	
	glm::mat4 transform = glm::translate(glm::mat4(1), pos);
	
	glm::mat4 rotationX = glm::rotate(glm::mat4(1), rot.x, glm::vec3(1, 0, 0));
	glm::mat4 rotationY = glm::rotate(glm::mat4(1), rot.y, glm::vec3(0, 1, 0));
	glm::mat4 rotationZ = glm::rotate(glm::mat4(1), rot.z, glm::vec3(0, 0, 1));

	glm::mat4 rotation = rotationX * rotationY * rotationZ;

	glm::mat4 scale = glm::scale(glm::mat4(1), size);

	modelMtx = transform * rotation * scale;
}

glm::mat4 Entity::getModelMtx() { return modelMtx; }

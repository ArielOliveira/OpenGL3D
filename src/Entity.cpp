#include "Entity.hpp"

Entity::Entity() :
	pos(glm::vec4(0, 0, 0, 1)),
	rot(glm::vec4(0, 0, 0, 1)),
	size(1),
	modelMtx(glm::mat4(1))
{}

Entity::Entity(const Entity& entity) : 
	pos(entity.pos),
	rot(entity.rot),
	size(entity.size),
	modelMtx(entity.modelMtx) 
{}

Entity::~Entity() {}

void Entity::setPos(glm::vec4 pos) { this->pos = pos; }
glm::vec4 Entity::getPos() { return pos; }

void Entity::setRot(glm::vec4 rot) { this->rot = rot; }
glm::vec4 Entity::getRot() { return rot; }

void Entity::setSize(glm::vec4 size) { this->size = size; }
glm::vec4 Entity::getSize() { return size; }

void Entity::computeModelMtx() {	
	glm::mat4 transform = glm::translate(glm::mat4(1), glm::vec3(pos.x, pos.y, pos.z));
	
	glm::mat4 rotationX = glm::rotate(glm::mat4(1), rot.x, glm::vec3(1, 0, 0));
	glm::mat4 rotationY = glm::rotate(glm::mat4(1), rot.y, glm::vec3(0, 1, 0));
	glm::mat4 rotationZ = glm::rotate(glm::mat4(1), rot.z, glm::vec3(0, 0, 1));

	glm::mat4 rotation = rotationX * rotationY * rotationZ;

	glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(size.x, size.y, size.z));

	modelMtx = transform * rotation * scale;
}

glm::mat4 Entity::getModelMtx() { return modelMtx; }

glm::mat3 Entity::getNormalMtx() { return glm::mat3(glm::transpose(glm::inverse(modelMtx))); }

#pragma once
#include "State.hpp"

#include <glm.hpp>
#include <ext.hpp>

class Entity {
	protected:
		glm::vec4 pos;
		glm::vec4 size;
		glm::vec4 rot;

		glm::mat4 modelMtx;
	public:
		Entity();
		Entity(const Entity& entity);
		virtual ~Entity();

		void setPos(glm::vec4 pos);
		glm::vec4 getPos();

		void setRot(glm::vec4 rot);
		glm::vec4 getRot();

		void setSize(glm::vec4 size);
		glm::vec4 getSize();

		void computeModelMtx();
		glm::mat4 getModelMtx();

		glm::mat3 getNormalMtx();

		virtual void step(float deltaTime) = 0;	
};


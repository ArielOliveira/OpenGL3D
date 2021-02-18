#pragma once
#include <glm.hpp>
#include <ext.hpp>
#include <gtx/matrix_decompose.hpp>
#include "State.hpp"

class Entity {
	protected:
		glm::vec3 pos;
		glm::vec3 size;
		glm::vec3 rot;

		glm::mat4 modelMtx;
	public:
		Entity();
		Entity(const Entity& entity);
		virtual ~Entity();

		void setPos(glm::vec3 pos);
		glm::vec3 getPos();

		void setRot(glm::vec3 rot);
		glm::vec3 getRot();

		void setSize(glm::vec3 size);
		glm::vec3 getSize();

		void computeModelMtx();
		glm::mat4 getModelMtx();

		glm::mat3 getNormalMtx();

		virtual void step(float deltaTime) = 0;	
};


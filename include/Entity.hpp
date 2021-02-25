#pragma once
#include "State.hpp"
#include "Math.hpp"

class Entity {
	protected:
		glm::vec4 pos;
		glm::vec4 size;
		glm::vec4 rot;

		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;

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

		void setForward(glm::vec3 direction);
		glm::vec3 getForward();

		void setRight(glm::vec3 direction);
		glm::vec3 getRight();

		void setUp(glm::vec3 direction);
		glm::vec3 getUp();

		void computeModelMtx();
		glm::mat4 getModelMtx();

		glm::mat3 getNormalMtx();

		virtual void step(float deltaTime) = 0;	
};


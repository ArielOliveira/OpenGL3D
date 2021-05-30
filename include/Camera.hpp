#pragma once
#include "Entity.hpp"
#include "Input.hpp"

class Camera : public Entity {
	private:
		glm::mat4 projection;
		glm::vec3 clearColor;

		glm::vec3 upView;
	
		const float speed = 2.f;
	public:
		Camera();
		Camera(glm::vec4 position, glm::vec3 up, glm::vec3 forward, glm::vec3 clearColor, glm::mat4 projection, glm::vec3 upView = glm::vec3(0, 1, 0));

		~Camera();
		
		void setProjection(const glm::mat4& proj) { projection = proj; }
		const glm::mat4& getProjection() const { return projection; }

		void setClearColor(const glm::vec3& color) { clearColor = color; }
		const glm::vec3& getClearColor() const { return clearColor; }

		void setUpView(const glm::vec3 upView);
		const glm::vec3& getUpView() const;
		
		void prepare();
		void move(float timeStep);
		void step(float timeStep);
};


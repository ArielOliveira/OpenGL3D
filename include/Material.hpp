#pragma once
#include "GLSLShader.hpp"
#include "GLTexture.hpp"
#include "State.hpp"

class Material {
	private:
		GLSLShader* shader;
		GLTexture* texture;

		glm::vec3 color;
	public:
		Material(GLTexture* tex = nullptr, glm::vec3 color = glm::vec3(1.f, 1.f, 1.f), GLSLShader* shader = nullptr);
		
		void setShader(GLSLShader* shader);
		GLSLShader* getShader() const;

		void setTexture(GLTexture* tex);
		GLTexture* getTexture() const;

		void prepare(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
		
		void setColor(glm::vec3 color);
		glm::vec3 getColor();		
};


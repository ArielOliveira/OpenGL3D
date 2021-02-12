#pragma once
#include "GLSLShader.hpp"
#include "GLTexture.hpp"
#include "State.hpp"

class Material {
	private:
		GLSLShader* shader;
		GLTexture* texture;

	public:
		Material(GLTexture* tex = nullptr, GLSLShader* shader = nullptr);
		
		void setShader(GLSLShader* shader);
		GLSLShader* getShader() const;

		void setTexture(GLTexture* tex);
		GLTexture* getTexture() const;

		void prepare(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);		
};


#include "Material.hpp"

Material::Material(GLTexture* tex, GLSLShader* shader) {
	this->texture = tex;
	this->shader = shader;
}

void Material::setShader(GLSLShader* shader) { this->shader = shader; }
GLSLShader* Material::getShader() const { return shader; }

void Material::setTexture(GLTexture* tex) { this->texture = tex; }
GLTexture* Material::getTexture() const { return texture; }

void Material::prepare(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
	GLSLShader* shader = this->shader;

	if (!shader) 
		shader = State::defaultShader;

	shader->use();
	shader->setMatrix(State::defaultShader->getLocation("MVP"), MVP);

	if (texture)
		texture->bind();
}

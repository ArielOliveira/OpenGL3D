#include "Material.hpp"

Material::Material(GLTexture* tex, glm::vec3 color, GLSLShader* shader) {
	this->texture = tex;
	this->shader = shader;
	this->color = color;
}

void Material::setShader(GLSLShader* shader) { this->shader = shader; }
GLSLShader* Material::getShader() const { return shader; }

void Material::setTexture(GLTexture* tex) { this->texture = tex; }
GLTexture* Material::getTexture() const { return texture; }

void Material::setColor(glm::vec3 color) { this->color = color; }
glm::vec3 Material::getColor() { return color; }

void Material::prepare(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
	GLSLShader* shader = this->shader;

	if (!shader) 
		shader = State::defaultShader;
	else if (shader == State::lightShader) {
		shader->use();
		shader->setVec3(shader->getLocation("objectColor"), color);
		shader->setVec3(shader->getLocation("lightColor"), glm::vec3(1));
	}

	shader->use();
	shader->setMatrix(State::defaultShader->getLocation("MVP"), MVP);
	shader->setVec3(shader->getLocation("vColor"), color);

	

	if (texture)
		texture->bind();
}
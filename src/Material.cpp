#include "Material.hpp"

Material::Material() {
	color = glm::vec3(1);
	ambient = color;
	diffuse = glm::vec3(0);
	specular = glm::vec3(0);
	shineness = 0;

	texture = nullptr;
	shader = State::defaultShader;
}

Material::Material(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shineness, GLTexture* tex, GLSLShader* shader) {
	this->color = color;
	
	this->ambient = ambient; 
	this->diffuse = diffuse;
	this->specular = specular; 
	this->shineness = shineness;

	this->texture = tex;

	if (!shader)
		this->shader = State::defaultShader;
	else
		this->shader = shader;
}

void Material::setShader(GLSLShader* shader) { this->shader = shader; }
GLSLShader* Material::getShader() const { return shader; }

void Material::setTexture(GLTexture* tex) { this->texture = tex; }
GLTexture* Material::getTexture() const { return texture; }

void Material::setColor(glm::vec3 color) { this->color = color; }
glm::vec3 Material::getColor() { return color; }

void Material::setShineness(float shineness) { this->shineness = shineness; }
float Material::getShineness() { return shineness; }

void Material::prepare(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	GLSLShader* shader = this->shader;
	
	shader->use();
	shader->setMatrix(shader->getLocation("model"), modelMatrix);
	shader->setMatrix(shader->getLocation("view"), viewMatrix);
	shader->setMatrix(shader->getLocation("projection"), projectionMatrix);
	
	shader->setVec3(shader->getLocation("vColor"), color);
	shader->setVec3(shader->getLocation("material.ambient"), ambient);
	shader->setVec3(shader->getLocation("material.diffuse"), diffuse);
	shader->setVec3(shader->getLocation("material.specular"), specular);
	shader->setFloat(shader->getLocation("material.shineness"), shineness);

	if (texture)
		texture->bind();
}
#include "Material.hpp"

Material::Material() {
	ambient = glm::vec3(1);
	diffuse = glm::vec3(1);
	specular = glm::vec3(1);
	shineness = 32.f;

	texture = nullptr;
	shader = State::defaultShader;
}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shineness, GLTexture* tex, GLSLShader* shader) {
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

void Material::setAmbient(glm::vec3 color) { ambient = color; }
glm::vec3 Material::getAmbient() { return ambient; }

void Material::setDiffuse(glm::vec3 color) { diffuse = color; }
glm::vec3 Material::getDiffuse() { return diffuse; }

void Material::setSpecular(glm::vec3 color) { specular = color; }
glm::vec3 Material::getSpecular() { return specular; }

void Material::setShineness(float shineness) { this->shineness = shineness; }
float Material::getShineness() { return shineness; }

void Material::prepare(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat3 normalMatrix) {
	GLSLShader* shader = this->shader;
	
	shader->use();
	shader->setMat4x4(shader->getLocation("model"), modelMatrix);
	shader->setMat4x4(shader->getLocation("view"), viewMatrix);
	shader->setMat4x4(shader->getLocation("projection"), projectionMatrix);
	shader->setMat3x3(shader->getLocation("normalMatrix"), normalMatrix);
	
	shader->setVec3(shader->getLocation("material.ambient"), ambient);
	shader->setVec3(shader->getLocation("material.diffuse"), diffuse);
	shader->setVec3(shader->getLocation("material.specular"), specular);
	shader->setFloat(shader->getLocation("material.shineness"), shineness);

	if (texture)
		texture->bind();
}
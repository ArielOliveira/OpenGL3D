#include "Material.hpp"

Material::Material() {									    
	diffuseMap = new GLTexture(State::whiteMap, glm::vec2(1), 1);
	specularMap = new GLTexture(State::whiteMap, glm::vec2(1), 1);
	emissiveMap = new GLTexture(State::blackMap, glm::vec2(1), 1);

	shineness = 16.f;

	shader = State::defaultShader;

	hasTransparency = false;
}

Material::Material(const GLTexture* diffuseMap, const GLTexture* specularMap, const GLTexture* emissiveMap, const float& shineness, const bool& hasTransparency, const GLSLShader* shader) {
	this->diffuseMap = diffuseMap;
	this->specularMap = specularMap; 
	this->emissiveMap = emissiveMap;
	this->shineness = shineness;
	this->shader = shader;
	this->hasTransparency = hasTransparency;
}

void Material::setShader(const GLSLShader* shader) { this->shader = shader; }
const GLSLShader& Material::getShader() const { return *shader; }

void Material::setDiffuseMap(const GLTexture* diffuseMap) { this->diffuseMap = diffuseMap; }
const GLTexture& Material::getDiffuseMap() const { return *diffuseMap; }

void Material::setSpecularMap(const GLTexture* specularMap) { this->specularMap = specularMap; }
const GLTexture& Material::getSpecularMap() const { return *specularMap; }

void Material::setShineness(const float& shineness) { this->shineness = shineness; }
const float Material::getShineness() const { return shineness; }

void Material::setEmissiveMap(const GLTexture* emissiveMap) { this->emissiveMap = emissiveMap; }
const GLTexture& Material::getEmissiveMap() const { return *emissiveMap; }

void Material::setHasTransparency(const bool& hasTransparency) { this->hasTransparency = hasTransparency; }
const bool Material::isTransparent() const { return hasTransparency; }

void Material::prepare(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat3 normalMatrix, double time) {
	shader->use();

	shader->setMat4x4(shader->getLocation("model"), modelMatrix);
	shader->setMat4x4(shader->getLocation("view"), viewMatrix);
	shader->setMat4x4(shader->getLocation("projection"), projectionMatrix);
	shader->setMat3x3(shader->getLocation("normalMatrix"), normalMatrix);

	shader->setInt(shader->getLocation("material.diffuse"), 0);
	shader->setInt(shader->getLocation("material.specular"), 1);
	shader->setInt(shader->getLocation("material.emissive"), 2);

	shader->setInt(shader->getLocation("material.diffuseQuotient"), diffuseMap->getAtlasSize());
	shader->setInt(shader->getLocation("material.specularQuotient"), specularMap->getAtlasSize());
	shader->setInt(shader->getLocation("material.emissiveQuotient"), emissiveMap->getAtlasSize());
	
	shader->setFloat(shader->getLocation("material.shineness"), shineness);

	glActiveTexture(GL_TEXTURE0);
	diffuseMap->bind();
	
	glActiveTexture(GL_TEXTURE1);
	specularMap->bind();

	glActiveTexture(GL_TEXTURE2);
	emissiveMap->bind();
}
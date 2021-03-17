#include "Material.hpp"

Material::Material() {
	diffuseMap = State::defaultMaterial->diffuseMap;
	specularMap = State::defaultMaterial->specularMap;
	emissiveMap = State::defaultMaterial->emissiveMap;

	glm::ivec2 diffuseOffset;
	glm::ivec2 specularOffset;
	glm::ivec2 emissiveOffset;

	shineness = 32.f;

	shader = State::defaultShader;
}

Material::Material(GLTexture* diffuseMap, GLTexture* specularMap, GLTexture* emissiveMap, const float& shineness, GLSLShader* shader) {
	this->diffuseMap = diffuseMap;
	this->specularMap = specularMap; 
	this->emissiveMap = emissiveMap;
	this->shineness = shineness;
	this->shader = shader;
}

void Material::setShader(GLSLShader* shader) { this->shader = shader; }
GLSLShader* Material::getShader() const { return shader; }

void Material::setDiffuseMap(GLTexture* diffuseMap) { this->diffuseMap = diffuseMap; }
const GLTexture& Material::getDiffuseMap() const { return *diffuseMap; }

void Material::setSpecularMap(GLTexture* specularMap) { this->specularMap = specularMap; }
const GLTexture& Material::getSpecularMap() const { return *specularMap; }

void Material::setShineness(float shineness) { this->shineness = shineness; }
float Material::getShineness() { return shineness; }

void Material::setEmissiveMap(GLTexture* emissiveMap) { this->emissiveMap = emissiveMap; }
const GLTexture& Material::getEmissiveMap() const { return *emissiveMap; }

void Material::prepare(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat3 normalMatrix, double time) {
	//GLSLShader* shader = this->shader;
	
	//shader->use();

	/*shader->setMat4x4(shader->getLocation("model"), modelMatrix);
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
	emissiveMap->bind();*/
}
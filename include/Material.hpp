#pragma once
#include "GLSLShader.hpp"
#include "GLTexture.hpp"
#include "State.hpp"

class Material {
	private:
		GLSLShader* shader;
		GLTexture* diffuseMap;
		GLTexture* specularMap;
		GLTexture* emissiveMap;
		
		glm::vec3 ambientColor;
		
		float shineness;
	public:
		Material();
		Material(const glm::vec3& ambientColor, GLTexture* diffuseMap, GLTexture* specularMap, GLTexture* emissiveMap, const float& shineness, GLSLShader* shader = State::defaultShader);
		
		void setShader(GLSLShader* shader);
		GLSLShader* getShader() const;

		void setTexture(GLTexture* tex);
		GLTexture* getTexture() const;

		void prepare(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat3 normalMatrix);

		void setDiffuseMap(GLTexture* diffuseMap);
		const GLTexture& getDiffuseMap() const;

		void setSpecularMap(GLTexture* specularMap);
		const GLTexture& getSpecularMap() const;

		void setEmissiveMap(GLTexture* emissiveMap);
		const GLTexture& getEmissiveMap() const;


		void setShineness(float shineness);
		float getShineness();	
};


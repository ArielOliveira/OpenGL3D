#pragma once
#include "GLSLShader.hpp"
#include "GLTexture.hpp"
#include "State.hpp"
#include "Component.hpp"

class Material : public Component {
	private:
		GLSLShader* shader;
		GLTexture* diffuseMap;
		GLTexture* specularMap;
		GLTexture* emissiveMap;
		
		float shineness;
	public:
		Material();
		Material(GLTexture* diffuseMap, GLTexture* specularMap, GLTexture* emissiveMap, const float& shineness, GLSLShader* shader = State::defaultShader);
		
		void setShader(GLSLShader* shader);
		GLSLShader* getShader() const;

		void prepare(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat3 normalMatrix, double time);

		void setDiffuseMap(GLTexture* diffuseMap);
		const GLTexture& getDiffuseMap() const;

		void setSpecularMap(GLTexture* specularMap);
		const GLTexture& getSpecularMap() const;

		void setEmissiveMap(GLTexture* emissiveMap);
		const GLTexture& getEmissiveMap() const;

		void setShineness(float shineness);
		float getShineness();

        void* as() { return this; }	
};


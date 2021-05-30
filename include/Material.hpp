#pragma once
#include "GLSLShader.hpp"
#include "GLTexture.hpp"
#include "State.hpp"
#include "Component.hpp"

class Material : public Component {
	private:
		const GLSLShader* shader;
		const GLTexture* diffuseMap;
		const GLTexture* specularMap;
		const GLTexture* emissiveMap;
		
		float shineness;

		bool hasTransparency;
	public:
		Material();
		Material(const GLTexture* diffuseMap, const GLTexture* specularMap, const GLTexture* emissiveMap, const float& shineness, const bool& hasTransparency, const GLSLShader* shader = State::defaultShader);
		
		void setShader(const GLSLShader* shader);
		const GLSLShader& getShader() const;

		void prepare(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat3 normalMatrix, double time);

		void setDiffuseMap(const GLTexture* diffuseMap);
		const GLTexture& getDiffuseMap() const;

		void setSpecularMap(const GLTexture* specularMap);
		const GLTexture& getSpecularMap() const;

		void setEmissiveMap(const GLTexture* emissiveMap);
		const GLTexture& getEmissiveMap() const;

		void setShineness(const float& shineness);
		const float getShineness() const;

		void setHasTransparency(const bool& hasTransparency);
		const bool isTransparent() const;
};


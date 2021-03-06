#pragma once

#include "Object.hpp"

class Light : public Object {
    protected:
        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;

        std::string uniformName;

        int id;
    public:
        Light();
        Light(const Light& light);
        Light(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular);
        virtual ~Light();

        void setAmbient(const glm::vec4& color);
        const glm::vec4& getAmbient() const;

        void setDiffuse(const glm::vec4& color);
        const glm::vec4& getDiffuse() const;

        void setSpecular(const glm::vec4& color);
        const glm::vec4& getSpecular() const;

        virtual void step(float deltaTime);
};
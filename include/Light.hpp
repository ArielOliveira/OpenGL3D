#pragma once

#include "Cube.hpp"

class Light : public Model {
    protected:
        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;
        
    public:
        Light();
        Light(const Light& light);
        Light(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular);

        void setAmbient(const glm::vec4& color);
        const glm::vec4& getAmbient() const;

        void setDiffuse(const glm::vec4& color);
        const glm::vec4& getDiffuse() const;

        void setSpecular(const glm::vec4& color);
        const glm::vec4& getSpecular() const;

        virtual void step(float deltaTime);
};
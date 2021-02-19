#pragma once

#include "Cube.hpp"

class Light : public Model {
    private:
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        
    public:
        Light();
        Light(const Light& light);
        Light(const Model& model);

        void setAmbient(const glm::vec3& color);
        const glm::vec3& getAmbient() const;

        void setDiffuse(const glm::vec3& color);
        const glm::vec3& getDiffuse() const;

        void setSpecular(const glm::vec3& color);
        const glm::vec3& getSpecular() const;

        void step(float deltaTime);
};
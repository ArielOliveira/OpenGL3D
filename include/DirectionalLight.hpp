#pragma once

#include "Light.hpp"

class DirectionalLight : public Light {
    private:
        static int globalID;
    public:

        DirectionalLight();
        DirectionalLight(const DirectionalLight& dirLight);
        DirectionalLight(const glm::vec4& _direction, const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular);
        ~DirectionalLight();

        void step(float deltaTime);
};
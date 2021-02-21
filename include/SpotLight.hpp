#pragma once
#include "PointLight.hpp"

class SpotLight : public PointLight {
    private:
        glm::vec4 direction;
        float innerRadius;
        float outterRadius;
    public:
        SpotLight();
        SpotLight(const SpotLight& light);
        SpotLight(const glm::vec4 direction, const float& innerRadius, const float& outterRadius,
                  const float& constant, const float& linear, const float& quadratic,
                  const glm::vec4& ambient, const::glm::vec4& diffuse, const glm::vec4& specular);
        
        void setDirection(const glm::vec4 direction);
        const glm::vec4& getDirection() const;

        void setInnerRadius(const float& innerRadius);
        float getInnerRadius() const;

        void setOutterRadius(const float& outterRadius);
        float getOutterRadius() const;

        void step(float deltaTime);
};
#pragma once
#include "PointLight.hpp"

class SpotLight : public Light {
     private:
        static int globalID;
        
        float constant;
        float linear;
        float quadratic;

        float innerRadius;
        float outterRadius;

    public:
        SpotLight();
        SpotLight(const SpotLight& light);
        SpotLight(const glm::vec3 forward, const float& innerRadius, const float& outterRadius,
                  const float& constant, const float& linear, const float& quadratic,
                  const glm::vec4& ambient, const::glm::vec4& diffuse, const glm::vec4& specular);
        
        void setDirection(const glm::vec3 forward);
        const glm::vec3& getDirection() const;

        void setInnerRadius(const float& innerRadius);
        float getInnerRadius() const;

        void setOutterRadius(const float& outterRadius);
        float getOutterRadius() const;

        void step(float deltaTime);
};
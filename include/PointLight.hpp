#pragma once
#include "Light.hpp"

class PointLight : public Light {
    private:
        static int globalID;
    protected:
        float constant;
        float linear;
        float quadratic;

    public:
        PointLight();
        PointLight(const PointLight& light);
        PointLight(const float& constant, const float& linear, const float& quadratic,
                   const glm::vec4& ambient, const::glm::vec4& diffuse, const glm::vec4& specular);

        ~PointLight();

        void setConstant(const float& constant);
        float getConstant() const;

        void setLinear(const float& linear);
        float getLinear() const;

        void setQuadratic(const float& quadratic);
        float getQuadratic() const;

        virtual void step(float deltaTime);
};
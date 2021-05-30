#pragma once

#include "SpotLight.hpp"

SpotLight::SpotLight() : Light() {
    id = State::sLightsCount;
    State::sLightsCount++;
    uniformName = "sLights[" + std::to_string(id) + "]";

    constant = 1;
    linear = .09f;
    quadratic = .032f;

    innerRadius = 12.5f;
    outterRadius = 17.5f;
}

SpotLight::SpotLight(const SpotLight& light) : Light(light) {
    id = State::sLightsCount;
    State::sLightsCount++;
    uniformName = "sLights[" + std::to_string(id) + "]";

    constant = light.constant;
    linear = light.linear;
    quadratic = light.quadratic;

    innerRadius = light.innerRadius;
    outterRadius = light.outterRadius;
}

SpotLight::SpotLight(const glm::vec3 forward, const float& innerRadius, const float& outterRadius,
    const float& constant, const float& linear, const float& quadratic,
    const glm::vec4& ambient, const::glm::vec4& diffuse, const glm::vec4& specular) :
    Light(ambient, diffuse, specular) {
        id = State::sLightsCount;
        State::sLightsCount++;
        uniformName = "sLights[" + std::to_string(id) + "]";

        this->constant = constant;
        this->linear = linear;
        this->quadratic = quadratic;

        this->forward = forward;
        this->innerRadius = innerRadius;
    }

SpotLight::~SpotLight() {
    State::sLightsCount--;
}

void SpotLight::setInnerRadius(const float& innerRadius) { this->innerRadius = innerRadius; }
float SpotLight::getInnerRadius() const { return innerRadius; }

void SpotLight::setOutterRadius(const float& outterRadius) { this->outterRadius = outterRadius; }
float SpotLight::getOutterRadius() const { return outterRadius; }
        
void SpotLight::step(float deltaTime)  {
    Light::step(deltaTime);

    const GLSLShader* shader = &getComponent<Material>()->getShader();

    int dir = glGetUniformLocation(shader->getID(), (uniformName + ".direction").c_str());
    int p = glGetUniformLocation(shader->getID(), (uniformName + ".position").c_str());

    int c = glGetUniformLocation(shader->getID(), (uniformName + ".constant").c_str());
    int l = glGetUniformLocation(shader->getID(), (uniformName + ".linear").c_str());
    int q = glGetUniformLocation(shader->getID(), (uniformName + ".quadratic").c_str());

    int inner = glGetUniformLocation(shader->getID(), (uniformName + ".innerRadius").c_str());
    int outter = glGetUniformLocation(shader->getID(), (uniformName + ".outterRadius").c_str());

    int spotCount = glGetUniformLocation(shader->getID(), "S_LIGHTS");

    shader->setVec4(dir, glm::vec4(forward, 0));
    
    shader->setVec4(p, pos);
    shader->setFloat(c, constant);
    shader->setFloat(l, linear);
    shader->setFloat(q, quadratic);

    shader->setFloat(inner, cos(glm::radians(innerRadius)));
    shader->setFloat(outter, cos(glm::radians(outterRadius)));
    
    shader->setInt(spotCount, State::sLightsCount);
}
#pragma once

#include "PointLight.hpp"

PointLight::PointLight() : Light() {
    id = State::pLightsCount;
    State::pLightsCount++;
    uniformName = "pLights[" + std::to_string(id) + "]";

    constant = 1;
    linear = .09f;
    quadratic = .032f;
}

PointLight::PointLight(const PointLight& light) : Light(light),
    constant(light.constant),
    linear(light.linear),
    quadratic(light.quadratic) {
        id = State::pLightsCount;
        State::pLightsCount++;
        uniformName = "pLights[" + std::to_string(id) + "]";

        pos = light.pos;
    }

PointLight::PointLight(const float& constant, const float& linear, const float& quadratic,
                       const glm::vec4& ambient, const::glm::vec4& diffuse, const glm::vec4& specular) : 
    Light(ambient, diffuse, specular) {
    id = State::pLightsCount;
    State::pLightsCount++;
    uniformName = "pLights[" + std::to_string(id) + "]";

    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

PointLight::~PointLight() {
    State::pLightsCount--;
}

void PointLight::setConstant(const float& constant) { this->constant = constant; }
float PointLight::getConstant() const { return constant; }

void PointLight::setLinear(const float& linear) { this->linear = linear; }
float PointLight::getLinear() const { return linear; }

void PointLight::setQuadratic(const float& quadratic) { this->quadratic = quadratic; }
float PointLight::getQuadratic() const { return quadratic; }

void PointLight::step(float deltaTime) {
    Light::step(deltaTime);

    const GLSLShader* shader = &getComponent<Material>()->getShader();
    int p = glGetUniformLocation(shader->getID(), (uniformName + ".position").c_str());
    int c = glGetUniformLocation(shader->getID(), (uniformName + ".constant").c_str());
    int l = glGetUniformLocation(shader->getID(), (uniformName + ".linear").c_str());
    int q = glGetUniformLocation(shader->getID(), (uniformName + ".quadratic").c_str());

    int pointCount = glGetUniformLocation(shader->getID(), "P_LIGHTS");

    shader->setVec4(p, pos);
    shader->setFloat(c, constant);
    shader->setFloat(l, linear);
    shader->setFloat(q, quadratic);

    shader->setInt(pointCount, State::pLightsCount);
}
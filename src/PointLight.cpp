#pragma once

#include "PointLight.hpp"

PointLight::PointLight() : Light() {
    constant = 1;
    linear = .09f;
    quadratic = .032f;

    meshList.clear();
    materialList.clear();
    Cube cube;
   
    addMesh(
        cube.getMesh(0), 
        new Material(
            State::defaultTexture,
            State::blackTexture,
            State::defaultTexture,
            0.f)
    );

    pos = glm::vec4(0, 0, 0, 1);
}

PointLight::PointLight(const PointLight& light) : Light(light),
    constant(light.constant),
    linear(light.linear),
    quadratic(light.quadratic) {
        pos = light.pos;
    }

PointLight::PointLight(const float& constant, const float& linear, const float& quadratic,
                       const glm::vec4& ambient, const::glm::vec4& diffuse, const glm::vec4& specular) : 
    Light(ambient, diffuse, specular) {
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

void PointLight::setConstant(const float& constant) { this->constant = constant; }
float PointLight::getConstant() const { return constant; }

void PointLight::setLinear(const float& linear) { this->linear = linear; }
float PointLight::getLinear() const { return linear; }

void PointLight::setQuadratic(const float& quadratic) { this->quadratic = quadratic; }
float PointLight::getQuadratic() const { return quadratic; }

void PointLight::step(float deltaTime) {
    Light::step(deltaTime);

    GLSLShader* shader = materialList[0]->getShader();

    shader->setFloat(shader->getLocation("light.constant"), constant);
    shader->setFloat(shader->getLocation("light.linear"), linear);
    shader->setFloat(shader->getLocation("light.quadratic"), quadratic);
}
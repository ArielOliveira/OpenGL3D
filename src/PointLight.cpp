#pragma once

#include "PointLight.hpp"

int PointLight::globalID = 0;

PointLight::PointLight() : Light() {
    Mesh* mesh = new Mesh();
    Cube cube;
    id = globalID;
    globalID++;
    uniformName = "pLights[" + std::to_string(id) + "]";
    
    addMesh(
        cube.getMesh(0), 
        new Material(
            State::defaultTexture,
            State::blackTexture,
            State::defaultTexture,
            0.f)
    );


    constant = 1;
    linear = .09f;
    quadratic = .032f;

    pos = glm::vec4(0, 0, 0, 1);
}

PointLight::PointLight(const PointLight& light) : Light(light),
    constant(light.constant),
    linear(light.linear),
    quadratic(light.quadratic) {
        id = globalID;
        globalID++;
        uniformName = "pLights[" + std::to_string(id) + "]";

        pos = light.pos;
    }

PointLight::PointLight(const float& constant, const float& linear, const float& quadratic,
                       const glm::vec4& ambient, const::glm::vec4& diffuse, const glm::vec4& specular) : 
    Light(ambient, diffuse, specular) {
    id = globalID;
    globalID++;
    uniformName = "pLights[" + std::to_string(id) + "]";

    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

PointLight::~PointLight() {
    globalID--;
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

    int c = glGetUniformLocation(shader->getID(), (uniformName + ".constant").c_str());
    int l = glGetUniformLocation(shader->getID(), (uniformName + ".linear").c_str());
    int q = glGetUniformLocation(shader->getID(), (uniformName + ".quadratic").c_str());

    shader->setFloat(c, constant);
    shader->setFloat(l, linear);
    shader->setFloat(q, quadratic);
}
#include "Light.hpp"
#include <glfw3.h>

Light::Light() : Object() {
    ambient = glm::vec4(.6f, .6f, .6f, 1);
    diffuse = glm::vec4(1.f, 1.f, 1.f, 1);
    specular = glm::vec4(1, 1, 1, 1);
    addComponent<Material>(State::defaultLightMaterial);
}

Light::Light(const Light& light) : Object(light),
    ambient(light.ambient),
    diffuse(light.diffuse),
    specular(light.specular)
    {}

Light::Light(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular) : Object() {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

Light::~Light() {}

void Light::setAmbient(const glm::vec4& color) { this->ambient = color; }
const glm::vec4& Light::getAmbient() const { return ambient;}

void Light::setDiffuse(const glm::vec4& color) { this->diffuse = color; }
const glm::vec4& Light::getDiffuse() const { return diffuse; }

void Light::setSpecular(const glm::vec4& color) { this->specular = color; }
const glm::vec4& Light::getSpecular() const { return specular; }

void Light::step(float deltaTime) {
    Object::step(deltaTime);
    
    const GLSLShader* shader = &getComponent<Material>()->getShader();

    shader->use();

    int amb = glGetUniformLocation(shader->getID(), (uniformName + ".ambient").c_str());
    int diff = glGetUniformLocation(shader->getID(), (uniformName + ".diffuse").c_str());
    int spec = glGetUniformLocation(shader->getID(), (uniformName + ".specular").c_str());

    shader->setVec4(amb, ambient);
    shader->setVec4(diff, diffuse);
    shader->setVec4(spec, specular);
}
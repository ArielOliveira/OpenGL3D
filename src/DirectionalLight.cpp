#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight() : Light() {
    id = State::dLightsCount;
    State::dLightsCount++;
    uniformName = "dLights[" + std::to_string(id) + "]";

    forward = glm::vec3(-.2f, -1.f, -.3f);
}

DirectionalLight::DirectionalLight(const DirectionalLight& dirLight) : 
    Light(dirLight) {
        id = State::dLightsCount;
        State::dLightsCount++;
        uniformName = "dLights[" + std::to_string(id) + "]";
    }

DirectionalLight::DirectionalLight(const glm::vec4& _direction, const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular) : 
    Light(ambient, diffuse, specular) {
        id = State::dLightsCount;
        State::dLightsCount++;
         uniformName = "dLights[" + std::to_string(id) + "]";
    }

DirectionalLight::~DirectionalLight() {
    State::dLightsCount--;
}

void DirectionalLight::step(float deltaTime) {
    Light::step(deltaTime);

    GLSLShader* shader = getComponent<Material>()->getShader();
    int dir = glGetUniformLocation(shader->getID(), (uniformName + ".direction").c_str());

    int dirCount = glGetUniformLocation(shader->getID(), "D_LIGHTS");

    shader->setVec4(dir, glm::vec4(forward, 0));

    shader->setInt(dirCount, State::dLightsCount);
}


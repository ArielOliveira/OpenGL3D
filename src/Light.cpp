#include "Light.hpp"

Light::Light() : Entity() {
    mesh = nullptr;
    material = new Material(glm::vec3(1), 
                            glm::vec3(1), 
                            glm::vec3(0), 
                            glm::vec3(0), 
                            0);
    intensity = 1.f;
}

Light::Light(const Light& light) : Entity(light) {
    this->intensity = light.intensity;
}

Light::Light(const Mesh& mesh,  const Material& material, float intensity) {
    this->mesh = new Mesh(mesh);
    this->material = new Material(material);
    this->intensity = intensity;
}

void Light::setIntensity(float intensity) { this->intensity = intensity; }
float Light::getIntensity() { return intensity; }

void Light::step(float deltaTime) {
    computeModelMtx();
    
    GLSLShader* shader = material->getShader();

    if (!shader)
        shader = State::defaultShader;

    shader->setVec3(shader->getLocation("vLightColor"), material->getColor());
    shader->setVec3(shader->getLocation("vLightPosition"), pos);
    shader->setFloat(shader->getLocation("vLightIntensity"), intensity);
}
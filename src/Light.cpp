#include "Light.hpp"
#include <glfw3.h>

Light::Light() : Model() {
    Cube cube;
    
    unsigned char map[] = { 255, 255, 255 };
    GLTexture texture(map, glm::vec2(1));
   
    addMesh(
        new Mesh(*cube.getMesh(0)), 
        new Material(
            glm::vec3(.2f),
            new GLTexture(texture),
            new GLTexture(texture),
            new GLTexture(texture),
            128.f
        )
    );

    ambient = glm::vec3(.5f);
    diffuse = glm::vec3(.5f);
    specular = glm::vec3(1.f);

    step(0);
}

Light::Light(const Light& light) : Model(light) {}

Light::Light(const Model& model) : Model(model) {
    ambient = glm::vec3(.5f);
    diffuse = glm::vec3(.5f);
    specular = glm::vec3(1.f);

    step(0);
}

void Light::setAmbient(const glm::vec3& color) { this->ambient = color; }
const glm::vec3& Light::getAmbient() const { return ambient;}

void Light::setDiffuse(const glm::vec3& color) { this->diffuse = color; }
const glm::vec3& Light::getDiffuse() const { return diffuse; }

void Light::setSpecular(const glm::vec3& color) { this->specular = color; }
const glm::vec3& Light::getSpecular() const { return specular; }

void Light::step(float deltaTime) {
    computeModelMtx();
    
    GLSLShader* shader = materialList[0]->getShader();

    shader->use();
    shader->setVec3(shader->getLocation("light.position"), pos);
    shader->setVec3(shader->getLocation("light.ambient"), ambient);
    shader->setVec3(shader->getLocation("light.diffuse"), diffuse);
    shader->setVec3(shader->getLocation("light.specular"), specular);
}
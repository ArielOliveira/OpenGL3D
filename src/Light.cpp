#include "Light.hpp"
#include <glfw3.h>

Light::Light() : Model() {
    Mesh* mesh = new Mesh();
    mesh->addVertex(vertex_t{glm::vec4(0), glm::vec4(0), glm::vec2(0)});
    mesh->addTriangleIdx(0, 1, 2);
    mesh->setVertexCount(4);
    mesh->setTextCount(2);
    
    addMesh(
        mesh, 
        new Material(
            State::defaultTexture,
            State::blackTexture,
            State::defaultTexture,
            0.f)
    );

    ambient = glm::vec4(.2f, .2f, .2f, 1);
    diffuse = glm::vec4(.5f, .5f, .5f, 1);
    specular = glm::vec4(1, 1, 1, 1);

    pos = glm::vec4(.0f, -1.f, .0f, .0f);
}

Light::Light(const Light& light) : Model(light),
    ambient(light.ambient),
    diffuse(light.diffuse),
    specular(light.specular)
    {}

Light::Light(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular) : Light() {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

void Light::setAmbient(const glm::vec4& color) { this->ambient = color; }
const glm::vec4& Light::getAmbient() const { return ambient;}

void Light::setDiffuse(const glm::vec4& color) { this->diffuse = color; }
const glm::vec4& Light::getDiffuse() const { return diffuse; }

void Light::setSpecular(const glm::vec4& color) { this->specular = color; }
const glm::vec4& Light::getSpecular() const { return specular; }

void Light::step(float deltaTime) {
    computeModelMtx();
    
    GLSLShader* shader = materialList[0]->getShader();

    shader->use();
    shader->setVec4(shader->getLocation("light.position"), pos);
    shader->setVec4(shader->getLocation("light.ambient"), ambient);
    shader->setVec4(shader->getLocation("light.diffuse"), diffuse);
    shader->setVec4(shader->getLocation("light.specular"), specular);
}
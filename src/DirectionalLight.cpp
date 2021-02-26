#include "DirectionalLight.hpp"

int DirectionalLight::globalID = 0;

DirectionalLight::DirectionalLight() : Light() {
    id = globalID;
    globalID++;
    uniformName = "dLights[" + std::to_string(id) + "]";

    Mesh* mesh = new Mesh();
    mesh->addVertex(vertex_t{glm::vec4(0), glm::vec4(0), glm::vec2(0)});
    mesh->addTriangleIdx(0, 1, 2);
    mesh->setVertexCount(4);
    mesh->setTextCount(2);
    
    addMesh(
        mesh, 
        new Material(
            State::blackTexture,
            State::blackTexture,
            State::blackTexture,
            0.f)
    );
    forward = glm::vec4(-.2f, -1.f, -.3f, .0f);
}

DirectionalLight::DirectionalLight(const DirectionalLight& dirLight) : 
    Light(dirLight) {
        id = globalID;
        globalID++;
        uniformName = "dLights[" + std::to_string(id) + "]";
    }

DirectionalLight::DirectionalLight(const glm::vec4& _direction, const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular) : 
    Light(ambient, diffuse, specular) {
        id = globalID;
        globalID++;
         uniformName = "dLights[" + std::to_string(id) + "]";
    }

DirectionalLight::~DirectionalLight() {
    globalID--;
}

void DirectionalLight::step(float deltaTime) {
    Light::step(deltaTime);

    GLSLShader* shader = materialList[0]->getShader();
    int dir = glGetUniformLocation(shader->getID(), (uniformName + ".direction").c_str());

    shader->setVec4(dir, glm::vec4(forward, 0));
}


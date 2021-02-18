#include "Light.hpp"
#include <glfw3.h>

Light::Light() : Entity() {
    mesh = nullptr;
    material = new Material(glm::vec3(.2f), 
                            glm::vec3(.5f), 
                            glm::vec3(.5f), 
                            128.f);
}

Light::Light(const Light& light) : Entity(light) {}

Light::Light(const Mesh& mesh,  const Material& material) {
    this->mesh = new Mesh(mesh);
    this->material = new Material(material);
}

void Light::step(float deltaTime) {
    glm::vec3 direction(0);

	direction.x = cos(glm::radians(rot.x)) * cos(glm::radians(rot.y));
	direction.y = -sin(glm::radians(rot.y));
	direction.z = sin(glm::radians(rot.x)) * cos(glm::radians(rot.y));

	rot.x = fmodf(rot.x + 64.f * deltaTime, 360.f);

	//pos = direction * 5.f;

	//modelMtx = glm::translate(glm::mat4(1), pos);

    computeModelMtx();

    glm::vec3 lightColor;
    lightColor.x = sin(glfwGetTime() * 2.0f);
    lightColor.y = sin(glfwGetTime() * 0.7f);
    lightColor.z = sin(glfwGetTime() * 1.3f);
  
    glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); 
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); 

    //material->setDiffuse(diffuseColor);
    //material->setAmbient(ambientColor);
    
    GLSLShader* shader = material->getShader();

    shader->use();
    shader->setVec3(shader->getLocation("light.position"), pos);
    shader->setVec3(shader->getLocation("light.ambient"), ambientColor);
    shader->setVec3(shader->getLocation("light.diffuse"), diffuseColor);
    shader->setVec3(shader->getLocation("light.specular"), material->getSpecular());
}
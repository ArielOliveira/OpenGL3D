#pragma once

#include "SpotLight.hpp"

SpotLight::SpotLight() :
    PointLight(),
    direction(glm::vec4(0, 0, -1, 0)),
    innerRadius(12.5f),
    outterRadius(17.5f) {

        pos = glm::vec4(0, 0, 0, 1);
        materialList.clear();
        meshList.clear();

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
    }

SpotLight::SpotLight(const SpotLight& light) : 
    PointLight(light),
    direction(light.direction),
    innerRadius(light.innerRadius),
    outterRadius(light.outterRadius)
    {}

SpotLight::SpotLight(const glm::vec4 direction, const float& innerRadius, const float& outterRadius,
    const float& constant, const float& linear, const float& quadratic,
    const glm::vec4& ambient, const::glm::vec4& diffuse, const glm::vec4& specular) :
    PointLight(constant, linear, quadratic, ambient, diffuse, specular) {
        this->direction = direction;
        this->innerRadius = innerRadius;
    }

void SpotLight::setDirection(const glm::vec4 direction) { this->direction = direction; }
const glm::vec4& SpotLight::getDirection() const { return direction;}

void SpotLight::setInnerRadius(const float& innerRadius) { this->innerRadius = innerRadius; }
float SpotLight::getInnerRadius() const { return innerRadius; }

void SpotLight::setOutterRadius(const float& outterRadius) { this->outterRadius = outterRadius; }
float SpotLight::getOutterRadius() const { return outterRadius; }
        
        
void SpotLight::step(float deltaTime)  {
    PointLight::step(deltaTime);

    GLSLShader* shader = materialList[0]->getShader();

    direction.x = cos(glm::radians(rot.x)) * cos(glm::radians(rot.y));
	direction.y = -sin(glm::radians(rot.y));
	direction.z = sin(glm::radians(rot.x)) * cos(glm::radians(rot.y));

    shader->setVec4(shader->getLocation("light.direction"), direction);
    shader->setFloat(shader->getLocation("light.innerRadius"), cos(glm::radians(innerRadius)));
    shader->setFloat(shader->getLocation("light.outterRadius"), cos(glm::radians(outterRadius)));
}
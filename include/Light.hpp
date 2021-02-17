#pragma once

#include "Model.hpp"

class Light : public Entity {
    private:
        float intensity;

        Mesh* mesh;
        Material* material;
    public:
        Light();
        Light(const Light& light);
        Light(const Mesh& mesh, const Material& material, float intensity);

        void setIntensity(float intensity);
        float getIntensity();

        void step(float deltaTime);
};
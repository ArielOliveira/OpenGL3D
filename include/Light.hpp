#pragma once

#include "Model.hpp"

class Light : public Entity {
    private:
        Mesh* mesh;
        Material* material;
    public:
        Light();
        Light(const Light& light);
        Light(const Mesh& mesh, const Material& material);

        void step(float deltaTime);
};
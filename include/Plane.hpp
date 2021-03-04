#pragma once

#include "Model.hpp"

class Plane : public Model {
    private:
        int vertexCount;

        Mesh* generate();
    public:
        Plane();
        Plane(int vertexCount, const Material& material);
        Plane(const Plane& plane);
        ~Plane();
};
#pragma once

#include "Object.hpp"

class Plane : public Object {
    private:
        int gridSize;

        Mesh* generate();
    public:
        Plane();
        Plane(int gridSize, Material* material);
        Plane(const Plane& plane);

        ~Plane();
};
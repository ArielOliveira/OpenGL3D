#pragma once

#include "Object.hpp"

class Plane : public Object {
    private:
        int vertexCount;

        Mesh* generate();
    public:
        Plane();
        Plane(int vertexCount, Material* material, bool hasTransparency);
        Plane(const Plane& plane);
        ~Plane();
};
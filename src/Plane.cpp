#include "Plane.hpp"

Plane::Plane() : Object() {
    vertexCount = 2;
    addComponent<Mesh>(generate());
    addComponent<Material>(new Material());
}

Plane::Plane(int vertexCount, Material* material, bool hasTransparency) : Object() {
    this->vertexCount = vertexCount;
    addComponent<Mesh>(generate());
    addComponent<Material>(material);
    //this->hasTransparency = hasTransparency;
}

Plane::Plane(const Plane& plane) :
    Object(plane), 
    vertexCount(plane.vertexCount)
    {}

Plane::~Plane() {
    Object::~Object();
}

Mesh* Plane::generate() {
    if ((!vertexCount) || (vertexCount & vertexCount-1))
        vertexCount = 2;

    int sizeX = vertexCount;
    int sizeY = vertexCount;

    Mesh* grid = new Mesh();

    grid->setVertexCount(4);
    grid->setTextCount(2);

    for (int z = 0; z < sizeY; z++) {
        for (int x = 0; x < sizeX; x++) {
            grid->addVertex({glm::vec4(x, 0, z, 1),
                             glm::vec4(0, 1, 0, 0),
                             glm::vec2(x/(sizeX-1), z/(sizeY-1))});
        }
    }

    int row = 0;
    int square = sizeX*sizeY;
    for (int x = 0; x < square; x++) {
        grid->addTriangleIdx(x, (sizeX-1) + x,  (sizeX-1) + x + 1);
        grid->addTriangleIdx((sizeX-1) + x + 1, x + 1,  x);
    }

    return grid;
}
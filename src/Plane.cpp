#include "Plane.hpp"
#include <random>

Plane::Plane() : Object() {
    gridSize = 2;
    addComponent<Mesh>(generate());
    addComponent<Material>(State::defaultMaterial);
}

Plane::Plane(int gridSize, Material* material) : Object() {
    this->gridSize = gridSize;
    addComponent<Mesh>(generate());
    addComponent<Material>(material);
}

Plane::Plane(const Plane& plane) :
    Object(plane), 
    gridSize(plane.gridSize)
    {}

Plane::~Plane() {
    Object::~Object();
}

Mesh* Plane::generate() {
    int vertices = gridSize*2;

    //float** heightMap = generateHeights();

    Mesh* grid = new Mesh();

    grid->setVertexCount(4);
    grid->setTextCount(2);

    for (int z = 0; z < vertices; z++) {
        for (int x = 0; x < vertices; x++) {
            grid->addVertex({glm::vec4(x, 0, z, 1),
                             glm::vec4(0, 1, 0, 0),
                             glm::vec2(x/(vertices-1), z/(vertices-1))});
        }
    }

    int count = 0;
    int vertCount = grid->getVertList()->size()-1;
    for (int x = 0; x < vertCount; x++) {
        if (count < vertices-1) {
            grid->addTriangleIdx(x, (vertices) + x,  (vertices) + x + 1);
            grid->addTriangleIdx((vertices) + x + 1, x + 1,  x);
            count++;
        } else { count = 0; }
    }

    return grid;
}

void diamondStep(float** heightMap, float tl, float tr, float bl, float br) {
   
}

void squareStep(float** heightMap, int size) {

}

void diamondSquare(float** heightMap, int size) {
    int half = size /2;

    if (half < 1)
        return;
}

float** generateHeights(int size) {
    float maxHeight = 3;

    float** heightMap = new float*[size];

    for (int i = 0; i < size; i++)
        heightMap[i] = new float[size];

    for (int i = 0; i <size; i++) {
        for (int j = 0; j < size; j++) {
            heightMap[i][j] = 0;
        }
    }

    heightMap[0][0] = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX))) * maxHeight;
    heightMap[0][size-1] = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX))) * maxHeight;
    heightMap[size-1][0] = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX))) * maxHeight;
    heightMap[size-1][size-1] = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX))) * maxHeight;

    std::cout << heightMap[0][0] << std::endl;

    float middle = (heightMap[size-1][0] + heightMap[size-1][size-1] + heightMap[0][0] + heightMap[0][size-1]) / 4;
    
    heightMap[size/2][size/2] = middle;

    diamondSquare(heightMap, size);

    return heightMap;
}
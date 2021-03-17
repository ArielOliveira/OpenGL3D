#pragma once

class Material;
class Mesh;

class Component {
    public:
        virtual void* as() { return nullptr; }
};
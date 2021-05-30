#pragma once

#include "Entity.hpp"
#include "Component.hpp"
#include "Material.hpp"

#include <typeinfo>
#include <typeindex>
#include <unordered_map>

class Object : public Entity {
    private:
        std::unordered_map<std::type_index, Component*> components;
        std::vector<Object*> childs;
        Object* parent;
    public:
        Object();
        Object(const Object& object);

        ~Object();

        template <typename T>
        void addComponent(T* component) { components.insert(std::pair<std::type_index, Component*>(typeid(T), component)); }

        template<typename T>
        T* getComponent() { return (T*) components[typeid(T)]; }

        template <typename T>
        void removeComponent() {
            auto it = components.find(typeid(T));
            if (it != components.end())
                components.erase(it);
        }

        virtual void step(float deltaTime);
};
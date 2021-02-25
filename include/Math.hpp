#pragma once

#include <glm.hpp>
#include <ext.hpp>

class Math {
    public:
        static glm::vec4 eulerToDirection(glm::vec4 rotation) {
            glm::vec4 direction(0);
            direction.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
	        direction.y = -sin(glm::radians(rotation.y));
	        direction.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));

            return direction;
        }
};
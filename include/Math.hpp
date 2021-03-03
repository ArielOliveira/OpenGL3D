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

        static glm::vec3 QuaternionToVector(glm::quat quat, glm::vec3 vec) {
	        float num = quat.x * 2.f;
	        float num2 = quat.y * 2.f;
	        float num3 = quat.z * 2.f;
	        float num4 = quat.x * num;
	        float num5 = quat.y * num2;
	        float num6 = quat.z * num3;
	        float num7 = quat.x * num2;
	        float num8 = quat.x * num3;
	        float num9 = quat.y * num3;
	        float num10 = quat.w * num;
	        float num11 = quat.w * num2;
	        float num12 = quat.w * num3;
	        glm::vec3 result(0);
	        result.x = (1.f - (num5 + num6)) * vec.x + (num7 - num12) * vec.y + (num8 + num11) * vec.z;
	        result.y = (num7 + num12) * vec.x + (1.f - (num4 + num6)) * vec.y + (num9 - num10) * vec.z;
	        result.z = (num8 - num11) * vec.x + (num9 + num10) * vec.y + (1.f - (num4 + num5)) * vec.z;
	        
            return result;
        }

        static glm::quat getRotation(glm::vec3 dir, float angle) {
            glm::quat rotation = glm::quat((float)sin(angle/2)*dir.x,
                                    (float)sin(angle/2)*dir.y,
                                    (float)sin(angle/2)*dir.z,
                                    (float)cos(angle/2));
        
            return rotation;
        }
};
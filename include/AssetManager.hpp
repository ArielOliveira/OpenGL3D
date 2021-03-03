#pragma once

#include <iostream>
#include <string>
#include <glm.hpp>
#include <map>

#include "stb_image.h"

class AssetManager {
    public:
        static std::map<std::string, int> loadedTextures;
        static unsigned char* textureFromFile(std::string name, std::string path, glm::ivec2& size, int& channels);
        static void freeSTBI(unsigned char* texture);
};
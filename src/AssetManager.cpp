#include "AssetManager.hpp"

std::map<std::string, int> AssetManager::loadedTextures;

unsigned char* AssetManager::textureFromFile(std::string name, std::string path, glm::ivec2& size, int& channels) {
    stbi_set_flip_vertically_on_load(true);

	unsigned char* texture = stbi_load((path + name).c_str(), &size.x, &size.y, &channels, 0);
	
	if (!texture) {
		std::cout << "Couldn't find texture file: " << path + name << std::endl;
		exit(-1);
	}

	return texture;
}

void AssetManager::freeSTBI(unsigned char* texture) { if (texture) stbi_image_free(texture); }
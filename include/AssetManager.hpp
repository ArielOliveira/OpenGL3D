#pragma once

#include <iostream>
#include <string>
#include <glm.hpp>
#include <map>

#include "stb_image.h"

#include "Mesh.hpp"
#include "GLTexture.hpp"
#include "Material.hpp"
#include "Model.hpp"

struct MeshPair {
	Mesh* mesh;
	Material* material;
};

class AssetManager {
    public:
        static map<string, Mesh*> meshHash;
		static map<int, GLTexture*> textureHash;
		static map<string, GLSLShader*> shaderHash;

        static std::map<std::string, int> loadedTextures;
        static unsigned char* textureFromFile(std::string name, std::string path, glm::ivec2& size, int& channels);
        static void freeSTBI(unsigned char* texture);

        static GLTexture* loadTextures(aiMaterial* material, aiTextureType type, string typeName);
        static MeshPair processMesh(aiMesh *mesh, const aiScene *scene);
        static void processNode(aiNode *node, const aiScene *scene, Model* model);
        static Model* loadModel(string path); 
};
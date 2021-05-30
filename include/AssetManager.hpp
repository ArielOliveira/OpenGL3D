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

class AssetManager {
    public:
        static map<string, Mesh*> meshHash;
		static map<string, GLTexture*> textureHash;
		static map<string, GLSLShader*> shaderHash;

        static map<string, Model*> modelHash;

        static unsigned char* textureFromFile(std::string name, std::string path, glm::ivec2& size, int& channels);
        static void freeSTBI(unsigned char* texture);

        static GLTexture* loadTextures(aiMaterial* material, aiTextureType type, string typeName);
        static std::pair<Mesh*, Material*> processMesh(aiMesh *mesh, const aiScene *scene);
        static void processNode(aiNode *node, const aiScene *scene, Model* model);
        static void loadModel(string path); 
};
#include "AssetManager.hpp"

map<string, Mesh*> AssetManager::meshHash;
map<string, GLTexture*> AssetManager::textureHash;
map<string, GLSLShader*> AssetManager::shaderHash;

map<string, Model*> AssetManager::modelHash;

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


GLTexture* AssetManager::loadTextures(aiMaterial* material, aiTextureType type, string typeName) {
	int atlasSizeDivision = material->GetTextureCount(type);

	if (atlasSizeDivision == 0)
		return nullptr;

	if (atlasSizeDivision > 1) {
		std::cout << "Can't deal with multiple textures of the same type" << std::endl;
		exit(-1);
	}

	aiString name;
	glm::ivec2 size;
	int channels;
	GLTexture* glTexture = nullptr;

	material->GetTexture(type, 0, &name);

	auto it = textureHash.find(name.C_Str());
	unsigned char* texture;
	
	if (it != textureHash.end()) {
		return it->second;
	} else {
		texture = textureFromFile(name.C_Str(), texturePath, size, channels);
		
		glTexture = new GLTexture(texture, size, 1, channels);
		textureHash[name.C_Str()] = glTexture;

		return glTexture;
	}
}

std::pair<Mesh*, Material*> AssetManager::processMesh(aiMesh *mesh, const aiScene *scene) {
    Mesh* myMesh = new Mesh();
	Material* material = new Material();

	myMesh->setVertexCount(4);
	myMesh->setTextCount(2);

    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        glm::vec4 position;
		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;
		position.w = 1;
        
		glm::vec4 normal;
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;
		normal.w = 0;
		
		glm::vec2 texture(0);
		if (mesh->mTextureCoords[0]) {
			texture.x = mesh->mTextureCoords[0][i].x;
			texture.y = mesh->mTextureCoords[0][i].y;
		}

		myMesh->addVertex(vertex_t{position, normal, texture});
    }
    if (mesh->mFaces->mNumIndices == 3) {
		for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
    		aiFace face = mesh->mFaces[i];
			myMesh->addTriangleIdx(face.mIndices[0], face.mIndices[1], face.mIndices[2]);	
		}
	}  else {
		std::cout << "Invalid index number for a triangle" << std::endl;
		exit(-1);
	}

	// process material
    if(mesh->mMaterialIndex >= 0) {
        aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

		GLTexture* diffuse = loadTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
		if (diffuse)
			material->setDiffuseMap(diffuse);

		GLTexture* specular = loadTextures(mat, aiTextureType_SPECULAR, "texture_specular");
		if (specular)
			material->setSpecularMap(specular);
    }

    return {myMesh, material};
} 


void AssetManager::processNode(aiNode *node, const aiScene *scene, Model* model) {
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
		std::pair<Mesh*, Material*> pair = processMesh(mesh, scene);
		model->addMesh(pair.first, pair.second);
    }
			
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, model);
    }
}  

void AssetManager::loadModel(string path) {
	std::string filename = FileLoader<void>::extractFileNameNoExtension(path);
	
	auto it = modelHash.find(filename);

	if (it != modelHash.end()) {
		return;
	} else {
		Model* model = new Model();
    	Assimp::Importer import;
    	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        	cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        		exit(-1);
			}
    	
    	processNode(scene->mRootNode, scene, model);

		modelHash.insert(std::pair<std::string, Model*>(filename, model));
	}
}
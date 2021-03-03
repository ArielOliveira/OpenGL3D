#include "GLTexture.hpp"
#include "OpenGLDebugger.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLTexture::GLTexture(unsigned char* UVCoords, const glm::vec2& size, int atlasSize, int channels) {
	this->size = size;
	this->atlasSize = atlasSize;
	this->channels = channels;
	
	if (UVCoords)
		load(UVCoords);
	else {
		std::cout << "Empty texture, exiting." << std::endl; 
		exit(-1);
	}

	this->UVCoords = UVCoords;
}

GLTexture::GLTexture(std::string filename) {
	stbi_set_flip_vertically_on_load(true);
	atlasSize = 1;

	unsigned char* texture = stbi_load(filename.c_str(), &size.x, &size.y, &channels, 0);
	
	if (!texture) {
		std::cout << "Couldn't find texture file: " << filename << std::endl;
		exit(-1);
	}

	load(texture);

	stbi_image_free(texture);
}

GLTexture::GLTexture() :
	ID(0),
	size(0),
	atlasSize(1)
	{}

GLTexture::~GLTexture() {}

void GLTexture::load(const unsigned char* texture) {
	GLenum format;
	switch (channels) {
	case 1: format = GL_LUMINANCE;
		break;
	case 2: format = GL_LUMINANCE_ALPHA;
		break;
	case 3: format = GL_RGB;
		break;
	case 4: format = GL_RGBA;
		break;
	default:
		format = GL_RGBA;
		std::cout << "No color channel format found, assigning default format." << std::endl;
		break;
	}

	glGenTextures(1, &ID);
	bind();
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, texture);
	glGenerateMipmap(GL_TEXTURE_2D);
}

const unsigned char& GLTexture::getUVCoords() const { return *UVCoords;}

uint32_t GLTexture::getId() const { return ID; }

int GLTexture::getAtlasSize() const { return atlasSize; }
const glm::ivec2& GLTexture::getSize() const { return size; }
void GLTexture::bind() const { GLCall(glBindTexture(GL_TEXTURE_2D, ID)); }

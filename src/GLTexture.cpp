#include "GLTexture.hpp"
#include "OpenGLDebugger.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLTexture::GLTexture(const unsigned char* texture, const glm::vec2 size) {
	this->size = size;
	
	if (texture)
		load(texture);
	else {
		std::cout << "Empty texture, exiting." << std::endl; 
		exit(-1);
	}
}

GLTexture::GLTexture(const char* filename, int index) {
	stbi_set_flip_vertically_on_load(true);

	unsigned char* texture = stbi_load(filename, &size.x, &size.y, &channels, 0);
	
	if (!texture) {
		std::cout << "Couldn't find texture file: " << filename << std::endl;
		exit(-1);
	}

	load(texture);
	this->index = index;

	stbi_image_free(texture);
}

GLTexture::GLTexture() :
	ID(0),
	index(0),
	size(0)
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

uint32_t GLTexture::getId() const { return ID; }

void GLTexture::setIdx(const int& index) { this->index = index; }
int GLTexture::getIdx() const { return index; } 

const glm::ivec2& GLTexture::getSize() const { return size; }
void GLTexture::bind() const { GLCall(glBindTexture(GL_TEXTURE_2D, ID)); }

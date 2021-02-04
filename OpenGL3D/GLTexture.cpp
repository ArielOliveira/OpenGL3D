#include "GLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLTexture::GLTexture(const char* filename) {
	load(filename);
}

GLTexture::GLTexture() :
	ID(0),
	size(0)
	{}

GLTexture::~GLTexture() {}

void GLTexture::load(const char* filename) {
	//stbi_set_flip_vertically_on_load(true);

	unsigned char* texture = stbi_load(filename, &size.x, &size.y, &channels, 0);
	
	if (!texture)
		exit(-1);

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
	}

	glGenTextures(1, &ID);
	bind();
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, texture);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	stbi_image_free(texture);
}
uint32_t GLTexture::getId() const { return ID; }
const glm::ivec2& GLTexture::getSize() const { return size; }
void GLTexture::bind() const { glBindTexture(GL_TEXTURE_2D, ID); }

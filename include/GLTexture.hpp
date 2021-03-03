#pragma once
#include <string>
#include <cstdint>
#include <glm.hpp>
#include <glew.h>

class GLTexture {
	private:
		unsigned char* UVCoords;

		uint32_t ID;
		glm::ivec2 size;
		int channels;

		int atlasSize;

	public:
		GLTexture(unsigned char* UVCoords, const glm::vec2& size, int atlasSize, int channels = -1);
		GLTexture(std::string filename);
		GLTexture();
		~GLTexture();

		const unsigned char& getUVCoords() const;

		void load(const unsigned char* texture);
		
		uint32_t getId() const;
		
		int getAtlasSize() const;
		const glm::ivec2& getSize() const;
		void bind() const;
};


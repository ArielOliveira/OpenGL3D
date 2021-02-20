#pragma once
#include <cstdint>
#include <glm.hpp>
#include <glew.h>

class GLTexture {
	private:
		uint32_t ID;
		int index;
		glm::ivec2 size;
		int channels;

	public:
		GLTexture(const unsigned char* texture, const glm::vec2 size);
		GLTexture(const char* filename, int index);
		GLTexture();
		~GLTexture();

		void load(const unsigned char* texture);
		
		uint32_t getId() const;
		
		void setIdx(const int& index);
		int getIdx() const;

		const glm::ivec2& getSize() const;
		void bind() const;
};


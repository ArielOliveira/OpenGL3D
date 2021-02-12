#pragma once
#include <cstdint>
#include <glm/glm.hpp>
#include <GL/glew.h>

class GLTexture {
	private:
		uint32_t ID;
		glm::ivec2 size;
		int channels;

	public:
		GLTexture(const char* filename);
		GLTexture();
		~GLTexture();

		void load(const char* filename);
		uint32_t getId() const;
		const glm::ivec2& getSize() const;
		void bind() const;
};


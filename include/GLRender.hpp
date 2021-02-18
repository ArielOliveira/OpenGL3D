#pragma once
#include <glew.h>
#include <glm.hpp>
#include <ext.hpp>
#include <map>

#include "Model.hpp"
#include "World.hpp"

using std::map;

typedef struct glMeshAttribs_t {
	GLuint bufferID;
	GLuint indexArrayID;
	GLuint vertexArrayID;
} glMeshAttribs_t;

class GLRender {
	private:
		map<glm::uint32, glMeshAttribs_t> vMeshIDs;

	public:
		GLRender();

		bool init();

		void setupObj(Model* obj);
		void drawObject(Model* obj);
		void drawWorld(World* world);
};


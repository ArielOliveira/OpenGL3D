#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <map>

#include "Object3D.h"
#include "World.h"

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

		void setupObj(Object3D* obj);
		void drawObject(Mesh3D* mesh, Material* material);
		void drawWorld(World* world);
};


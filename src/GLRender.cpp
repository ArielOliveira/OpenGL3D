#include "GLRender.hpp"

GLRender::GLRender() {

}

bool GLRender::init() {
	if (glewInit() != GLEW_OK)
		return false;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);

	if (glGetError() != GL_NO_ERROR)
		return false;
	return true;
}

void GLRender::setupObj(Model* obj) {	
	for (int i = 0; i < obj->getMeshCount(); i++) {
		Mesh* mesh = obj->getMesh(i);
		GLSLShader* shader = obj->getMaterial(i).getShader();

		shader->use();

		std::vector<vertex_t>* vertices = mesh->getVertList();
		std::vector<glm::int32>* indices = mesh->getTriangleIdxList();

		glm::uint32 meshID = mesh->getMeshID();

		std::cout << vertices->size() << " " << indices->size() << " " << meshID << std::endl;

		GLCall(glGenVertexArrays(1, &vMeshIDs[meshID].bufferID));
		GLCall(glGenBuffers(1, &vMeshIDs[meshID].vertexArrayID));
		GLCall(glGenBuffers(1, &vMeshIDs[meshID].indexArrayID));

		GLCall(glBindVertexArray(vMeshIDs[meshID].bufferID));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vMeshIDs[meshID].vertexArrayID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(vertex_t), vertices->data(), GL_STATIC_DRAW));

		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vMeshIDs[meshID].indexArrayID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices->size(),
			indices->data(), GL_STATIC_DRAW));

		GLCall(glVertexAttribPointer(VERTEX_ATTRIB_IDX, mesh->getVertexCount(), GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)0));
		GLCall(glEnableVertexAttribArray(VERTEX_ATTRIB_IDX));

		GLCall(glVertexAttribPointer(NORMAL_ATTRIB_IDX, mesh->getVertexCount(), GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, normal)));
		GLCall(glEnableVertexAttribArray(NORMAL_ATTRIB_IDX));

		GLCall(glVertexAttribPointer(TEXT_ATTRIB_IDX, mesh->getTextCount(), GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, texture)));
		GLCall(glEnableVertexAttribArray(TEXT_ATTRIB_IDX));
	}
}

void GLRender::drawObject(Model* obj) {
	for (int i = 0; i < obj->getMeshCount(); i++) {
		Material material = obj->getMaterial(i);
		Mesh* mesh = obj->getMesh(i);	
		material.prepare(State::modelMatrix, State::viewMatrix, State::projectionMatrix, obj->getNormalMtx());
		GLCall(glBindVertexArray(vMeshIDs[mesh->getMeshID()].bufferID));
		GLCall(glDrawElements(GL_TRIANGLES, mesh->getTriangleIdxList()->size(), GL_UNSIGNED_INT, nullptr));
	}
}

void GLRender::drawWorld(World* world) {
	for (int i = 0; i < world->getNumObjects(); i++) {
		Model* obj = world->getObject(i);
		State::modelMatrix = obj->getModelMtx();
		drawObject(obj);
	}
	for (int i = 0; i < world->getNumLights(); i++) {
		Light* light = world->getLight(i);
		State::modelMatrix = light->getModelMtx();
		drawObject(light);
	}
}

#include "GLRender.hpp"

GLRender::GLRender() {

}

bool GLRender::init() {
	if (glewInit() != GLEW_OK)
		return false;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (glGetError() != GL_NO_ERROR)
		return false;
	return true;
}

void GLRender::setupObj(Object* obj) {	
	//for (int i = 0; i < obj->getMeshCount(); i++) {

		//const Mesh* mesh = obj->getMesh(i);
		//const GLSLShader* shader = &obj->getMaterial(i).getShader();

		const Mesh* mesh = obj->getComponent<Mesh>();
		const GLSLShader* shader = &obj->getComponent<Material>()->getShader();

		shader->use();

		const std::vector<vertex_t>* vertices = mesh->getVertList();
		const std::vector<glm::int32>* indices = mesh->getTriangleIdxList();

		glm::uint32 meshID = mesh->getMeshID();

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
	//}
}

void GLRender::drawObject(Object* obj) {
	Material* material = obj->getComponent<Material>();
	Mesh* mesh = obj->getComponent<Mesh>();	
	
	material->prepare(State::modelMatrix, State::viewMatrix, State::projectionMatrix, obj->getNormalMtx(), glfwGetTime());
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	GLCall(glBindVertexArray(vMeshIDs[mesh->getMeshID()].bufferID));
	GLCall(glDrawElements(GL_TRIANGLES, mesh->getTriangleIdxList()->size(), GL_UNSIGNED_INT, nullptr));
}

void GLRender::drawWorld(World* world) {
	for (int i = 0; i < world->getNumObjects(); i++) {
		Object* obj = world->getObject(i);
		State::modelMatrix = obj->getModelMtx();
		drawObject(obj);
	}

	map<float, Object*>* sorted = world->getSortedTransparent();

	for (auto it = sorted->rbegin(); it != sorted->rend(); ++it) {
		State::modelMatrix = it->second->getModelMtx();
		drawObject(it->second);
	}
}

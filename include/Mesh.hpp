#pragma once
#include <glm\glm.hpp>
#include <vector>


using std::vector;

struct vertex_t {
	glm::vec4 position;
	glm::vec4 color;
	glm::vec2 texture;
	
	vertex_t(glm::vec4 position, glm::vec4 color, glm::vec2 texture) {
		this->position = position;
		this->color = color;
		this->texture = texture;
	}
};

class Mesh {
	private:
		glm::uint32 meshID;
		
		glm::vec3 colorRGB;

		vector<vertex_t>* vVertList;
		vector<glm::int32>* vIdxList;
		
		int vertexCount;
		int textCount;
	public:
		static glm::uint32 globalMeshID;

		Mesh();
		Mesh(vector<vertex_t>* vertexList, vector<glm::int32>* indexList, int vertexCount, int textCount);
		~Mesh();

		glm::uint32 getMeshID();

		void addVertex(const vertex_t& vertex);
		void addTriangleIdx(const glm::int32& v1, const glm::int32& v2, const glm::int32& v3);
		
		void setVertexCount(const int& count);
		void setTextCount(const int& count);

		const int getVertexCount() const;
		const int getTextCount() const;
		

		vector<vertex_t>* getVertList();
		vector<glm::int32>* getTriangleIdxList();

		void setColorRGB(float r, float g, float b);
		glm::vec3 getColorRGB();
};


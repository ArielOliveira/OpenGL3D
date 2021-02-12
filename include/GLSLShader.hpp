#pragma once

#include "OpenGLDebugger.hpp"
#include "FileLoader.hpp"

#include <glm.hpp>
#include <ext.hpp>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <string>

using std::map;
using std::string;

const unsigned VERTEX_ATTRIB_IDX = 0;
const unsigned COLOR_ATTRIB_IDX = 1;
const unsigned TEXT_ATTRIB_IDX = 2;

class GLSLShader {
private:
	glm::uint32 programID;
	map<string, glm::uint32> vShaderAttribs;

	std::string parseShader(const std::string& filepath);
public:
	GLSLShader(const string& vertexPrg, const string& fragmentPrg);
	GLSLShader();

	~GLSLShader();

	void use() const;
	void setupAttribs();

	glm::uint32 compileShader(const glm::uint32& type, const std::string& source);
	glm::uint32 createShader(const std::string& vertexShader, const std::string& fragmentShader);
	glm::uint32 getID();

	const char* getError() const;

	glm::uint32 getLocation(const string& name);

	void setInt(const glm::uint32& loc, const int& val);
	void setFloat(const glm::uint32& loc, const float& val);
	void setVec3(const glm::uint32& loc, const glm::vec3& vec);
	void setVec4(const glm::uint32& loc, const glm::vec4& vec);
	void setMatrix(const glm::uint32& loc, const glm::mat4& matrix);
};


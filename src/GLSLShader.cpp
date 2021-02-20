#include "GLSLShader.hpp"

GLSLShader::GLSLShader(const string& vertexPrg, const string& fragmentPrg) {
	std::string vertexSource = parseShader(vertexPrg);
	std::string fragmentSource = parseShader(fragmentPrg);

	if (vertexSource == "") {
		std::cout << "Could not load vertex shader file. Exiting" << std::endl;
		exit(-1);
	}

	if (fragmentSource == "") {
		std::cout << "Could not load fragment shader file. Exiting" << std::endl;
		exit(-1);
	}

	createShader(vertexSource, fragmentSource);
	use();
	setupAttribs();
}

GLSLShader::GLSLShader() {
	programID = -1;
}

GLSLShader::~GLSLShader() {}

std::string GLSLShader::parseShader(const std::string& filepath) {
	std::fstream stream(filepath);

	std::string line;
	std::stringstream ss;

	while (getline(stream, line)) {
		ss << line << '\n';
	}

	return ss.str();
}

glm::uint32 GLSLShader::compileShader(const glm::uint32& type, const std::string& source) {
	unsigned id = glCreateShader(type); // Cria um objeto shader e atribui seu valor ao id
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr); // Carrega a string para ser c?digo fonte do shader especificado
	glCompileShader(id); // Compila o shader

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "O Shader " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " falhou ao compilar! " << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return -1;
	}
	return id;
}

glm::uint32 GLSLShader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
	programID = glCreateProgram(); // Cria um objeto de programa
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	if (vs == -1 || fs == -1)
		exit(-1);

	GLCall(glAttachShader(programID, vs)); // Liga o shader compilado ao objeto de programa
	GLCall(glAttachShader(programID, fs));

	GLCall(glBindAttribLocation(programID, VERTEX_ATTRIB_IDX, "vVertex"));
	GLCall(glBindAttribLocation(programID, NORMAL_ATTRIB_IDX, "vNormal"));
	GLCall(glBindAttribLocation(programID, TEXT_ATTRIB_IDX, "vTextCoords"));

	GLCall(glLinkProgram(programID));
	GLCall(glValidateProgram(programID));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return programID;
}


glm::uint32 GLSLShader::getID() { return programID; }

const char* GLSLShader::getError() const { return "0"; }

void GLSLShader::use() const { glUseProgram(programID); }

void GLSLShader::setupAttribs() {
	GLCall(vShaderAttribs["model"] = glGetUniformLocation(programID, "model"));
	GLCall(vShaderAttribs["view"] = glGetUniformLocation(programID, "view"));
	GLCall(vShaderAttribs["projection"] = glGetUniformLocation(programID, "projection"));
	GLCall(vShaderAttribs["normalMatrix"] = glGetUniformLocation(programID, "normalMatrix"));
	
	GLCall(vShaderAttribs["vLightPosition"] = glGetUniformLocation(programID, "vLightPosition"));

	GLCall(vShaderAttribs["fLightColor"] = glGetUniformLocation(programID, "fLightColor"));
	GLCall(vShaderAttribs["fLightIntensity"] = glGetUniformLocation(programID, "fLightIntensity"));
	
	GLCall(vShaderAttribs["material.diffuse"] = glGetUniformLocation(programID, "material.diffuse"));
	GLCall(vShaderAttribs["material.specular"] = glGetUniformLocation(programID, "material.specular"));
	GLCall(vShaderAttribs["material.emissive"] = glGetUniformLocation(programID, "material.emissive"));
	GLCall(vShaderAttribs["material.shineness"] = glGetUniformLocation(programID, "material.shineness"));

	GLCall(vShaderAttribs["light.position"] = glGetUniformLocation(programID, "light.position"));
	GLCall(vShaderAttribs["light.ambient"] = glGetUniformLocation(programID, "light.ambient"));
	GLCall(vShaderAttribs["light.diffuse"] = glGetUniformLocation(programID, "light.diffuse"));
	GLCall(vShaderAttribs["light.specular"] = glGetUniformLocation(programID, "light.specular"));
}

glm::uint32 GLSLShader::getLocation(const string& name) { return vShaderAttribs[name]; }

void GLSLShader::setInt(const glm::uint32& loc, const int& val) { glUniform1i(loc, val); }
void GLSLShader::setFloat(const glm::uint32& loc, const float& val) { glUniform1f(loc, val); }
void GLSLShader::setVec3(const glm::uint32& loc, const glm::vec3& vec) { glUniform3f(loc, vec.x, vec.y, vec.z); }
void GLSLShader::setVec4(const glm::uint32& loc, const glm::vec4& vec) { glUniform4f(loc, vec.x, vec.y, vec.z, vec.w); }
void GLSLShader::setMat4x4(const glm::uint32& loc, const glm::mat4& matrix) { glUniformMatrix4fv(loc, 1, false, glm::value_ptr(matrix)); }
void GLSLShader::setMat3x3(const glm::uint32& loc, const glm::mat3& matrix) { glUniformMatrix3fv(loc, 1, false, glm::value_ptr(matrix)); }


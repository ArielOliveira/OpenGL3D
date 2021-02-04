#include "GLSLShader.h"

GLSLShader::GLSLShader(const string& vertexPrg, const string& fragmentPrg) {
	createShader(vertexPrg, fragmentPrg);
	use();
	setupAttribs();
}

GLSLShader::GLSLShader() {
	programID = -1;
}

GLSLShader::~GLSLShader() {}

glm::uint32 GLSLShader::compileShader(const glm::uint32& type, const std::string& source) {
	unsigned id = glCreateShader(type); // Cria um objeto shader e atribui seu valor ao id
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr); // Carrega a string para ser código fonte do shader especificado
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
		return 0;
	}
	return id;
}

glm::uint32 GLSLShader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
	programID = glCreateProgram(); // Cria um objeto de programa
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(programID, vs)); // Liga o shader compilado ao objeto de programa
	GLCall(glAttachShader(programID, fs));

	GLCall(glBindAttribLocation(programID, VERTEX_ATTRIB_IDX, "vertex"));
	GLCall(glBindAttribLocation(programID, COLOR_ATTRIB_IDX, "vColor"));
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
	GLCall(vShaderAttribs["MVP"] = glGetUniformLocation(programID, "MVP"));
}

glm::uint32 GLSLShader::getLocation(const string& name) { return vShaderAttribs[name]; }

void GLSLShader::setInt(const glm::uint32& loc, const int& val) { glUniform1i(loc, val); }
void GLSLShader::setFloat(const glm::uint32& loc, const float& val) { glUniform1f(loc, val); }
void GLSLShader::setVec3(const glm::uint32& loc, const glm::vec3& vec) { glUniform3f(loc, vec.x, vec.y, vec.z); }
void GLSLShader::setVec4(const glm::uint32& loc, const glm::vec4& vec) { glUniform4f(loc, vec.x, vec.y, vec.z, vec.w); }
void GLSLShader::setMatrix(const glm::uint32& loc, const glm::mat4& matrix) { glUniformMatrix4fv(loc, 1, false, glm::value_ptr(matrix)); }


#include "Shader.h"

Shader::Shader() {

	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}


void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {

	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation) {

	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* fileLocation) {

	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist", fileLocation);
	}
	std::string line = " ";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) {

	shaderID = glCreateProgram();
	if (!shaderID) {
		printf("Error Creating Shader program!");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 }; //const oalrak tanýmladýðýmýz kodda sýkýntý olup olmadýðýný kontrol etmek için

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", &eLog);
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", &eLog);
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view");
}

void Shader::AddShader(GLuint theProgram, const char* shadercode, GLenum Shadertype) {
	GLuint theShader = glCreateShader(Shadertype);
	const GLchar* theCode[1];
	theCode[0] = shadercode;

	GLint codeLenght[1];
	codeLenght[0] = strlen(shadercode);
	glShaderSource(theShader, 1, theCode, codeLenght);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 }; //const oalrak tanýmladýðýmýz kodda sýkýntý olup olmadýðýný kontrol etmek için

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", Shadertype, &eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

GLuint Shader::GetProjectionLocation() {
	return uniformProjection;
}

GLuint Shader::GetModelLocation() {
	return uniformModel;
}

GLuint Shader::GetViewLocation() {
	return uniformView;
}

void Shader::UseShader() {
	glUseProgram(shaderID);
}

void Shader::ClearShader() {

	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
}

Shader::~Shader() {
	ClearShader();
}

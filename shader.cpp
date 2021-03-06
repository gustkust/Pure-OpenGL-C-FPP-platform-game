#include "shader.h"


char* Shader::readFile(const char* fileName) {
	int filesize;
	FILE* file;
	char* result;

	#pragma warning(suppress : 4996)
	file = fopen(fileName, "rb");
	if (file != NULL) {
		fseek(file, 0, SEEK_END);
		filesize = ftell(file);
		fseek(file, 0, SEEK_SET);
		result = new char[filesize + 1];
		#pragma warning(suppress : 6386)
		int readsize = fread(result, 1, filesize, file);
		result[filesize] = 0;
		fclose(file);

		return result;
	}
}


Shader::Shader(const char* vertexPath, const char* fragmentPath) {

	// create variable for vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// load shader file content to a variable
	const GLchar* vertexShaderSource = readFile(vertexPath);
	// connect variable to the source file
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// compile the file
	glCompileShader(vertexShader);

	// create variable for fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// load shader file content to a variable
	const GLchar* fragmentShaderFile = readFile(fragmentPath);
	// connect variable to the source file
	glShaderSource(fragmentShader, 1, &fragmentShaderFile, NULL);
	// compile the file
	glCompileShader(fragmentShader);

	// generate variable for shader program
	ID = glCreateProgram();

	// connect both compiled shader programs to a shader program variable
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// link the program
	glLinkProgram(ID);
}


void Shader::use() {
    glUseProgram(ID);
}


Shader::Shader() {}
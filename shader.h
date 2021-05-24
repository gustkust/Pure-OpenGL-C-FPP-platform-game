#ifndef SHADER_H
#define SHADER_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    char* readFile(const char* fileName);
    GLuint loadShader(GLenum shaderType, const char* fileName);
    void use();
    Shader();
private:
    // checks for shader compile errors
    void checkCompileErrors(GLuint shader, std::string type);
};


#endif
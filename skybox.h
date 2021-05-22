#ifndef SKYBOX_H
#define SKYBOX_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include <iostream>
#include <vector>
#include <string>
#include "shader.h"

using namespace std;


class Skybox {
public:
    Skybox();
    int VAO;
    int texture;
    Shader skyboxShader;
    void draw(glm::mat4 view, glm::mat4 projection);
};


#endif
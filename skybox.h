//skybox mySkybox();
//unsigned int cubemapTexture = mySkybox.load();
//Shader skyboxShader("6.2.skybox.vs", "6.2.skybox.fs");


//glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
//skyboxShader.use();
//view = glm::mat4(glm::mat3(myCam.getV()); // remove translation from the view matrix
//skyboxShader.setMat4("view", view);
//skyboxShader.setMat4("projection", projection);
//// skybox cube
//glBindVertexArray(mySkybox.VAO);
//glActiveTexture(GL_TEXTURE0);
//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//glDrawArrays(GL_TRIANGLES, 0, 36);
//glBindVertexArray(0);
//glDepthFunc(GL_LESS); // set depth function back to default


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
using namespace std;


class skybox {
public:
    skybox();
    unsigned int load();

    unsigned int VAO, VBO;
};
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "camera.h"
#include "model.h"
#include "skybox.h"
#include <iostream>
#include "collision.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// window size
float SCR_WIDTH = 1024;
float SCR_HEIGHT = 768;

// time
float lastTime = 0.0;
float deltaTime = 0.0;

// camera
camera myCam;


bool w_pressed = false;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_A) myCam.setSpeedLeft(15 * deltaTime);
        if (key == GLFW_KEY_D) myCam.setSpeedRight(15 * deltaTime);
        if (key == GLFW_KEY_W) {
            w_pressed = true;
            myCam.setSpeedForward(15 * deltaTime);
        }
        if (key == GLFW_KEY_S) myCam.setSpeedBackward(15 * deltaTime);
        if (key == GLFW_KEY_SPACE) myCam.jump(true);
        if (key == GLFW_KEY_C) myCam.newCrouch(true);
        if (key == GLFW_KEY_LEFT_SHIFT) {
            if (w_pressed) {
                myCam.setSpeedForward(3 * 15 * deltaTime);
            }
        }
    }
    if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_A) myCam.setSpeedLeft(0);
        if (key == GLFW_KEY_D) myCam.setSpeedRight(0);
        if (key == GLFW_KEY_W)
        {
            w_pressed = false;
            myCam.setSpeedForward(0);
        }
        if (key == GLFW_KEY_S) myCam.setSpeedBackward(0);
        if (key == GLFW_KEY_SPACE) myCam.jump(false);
        if (key == GLFW_KEY_C) myCam.newCrouch(false);
        if (key == GLFW_KEY_LEFT_SHIFT) {
            if (w_pressed) {
                myCam.setSpeedForward(15 * deltaTime);
            }
        }
    }
}


bool firstMouse = true;
void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
	myCam.mouseMovement(xPos, yPos, firstMouse);
	if (firstMouse) firstMouse = false;
}


GLFWwindow* GLFWsetup() {
    // init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //creating window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Jumping on roofs!", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Error creating GLFW window" << std::endl;
        glfwTerminate();
    }

    // setting context and callbacks
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    // makes cursor unable to go outside the window
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    return window;
}


int main() {
    // configure glfw and create a window
    GLFWwindow* window = GLFWsetup();

    // init glew
    glewExperimental = GL_TRUE;
    glewInit();

    // flip stb_image.h (to match opengl)
    stbi_set_flip_vertically_on_load(true);

    // makes models opaque
    glEnable(GL_DEPTH_TEST);

    // load shaders and create shader object
    Shader ourShader("model.vs", "model.fs");
    Shader skyboxShader("skybox.vs", "skybox.fs");

    // load model and create model object
    Model backpack("resources/models/backpack/backpack.obj");
    Model skull("resources/models/skull/12140_Skull_v3_L2.obj");
    Model tree("resources/models/tree/Tree.obj");
    Model crate("resources/models/Crate/Crate1.obj");

    // load skybox
    skybox mySkybox;
    unsigned int cubemapTexture = mySkybox.load();

    // main loop
    while (!glfwWindowShouldClose(window)) {
        float thisTime = glfwGetTime();
        deltaTime = thisTime - lastTime;
        lastTime = thisTime;

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        Collision box1(glm::vec3(0.0f, -10.0f, 0.0f), glm::vec3(30.0f, 1.0f, 30.0f));
        cout << box1.checkCollision(myCam.getPos()) << " " << "\n";

        myCam.positionChange(deltaTime, box1);

        // model, view and projection matrices setup
        glm::mat4 projection = glm::perspective(3.14f * 50.0f/180.0f, (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1f, 3000.0f);
        glm::mat4 view = myCam.getV();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        
        // backpack
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        ourShader.setMat4("model", model);
        backpack.Draw(ourShader);

        // skull
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(10.0f, 0.0f, 10.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        model = glm::rotate(model, 270.0f * 3.14f / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        ourShader.setMat4("model", model);
        skull.Draw(ourShader);

        // tree
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        ourShader.setMat4("model", model);
        tree.Draw(ourShader);

        // crate 3 x 3 x 3
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -10.0f, 0.0f));
        model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
        ourShader.setMat4("model", model);
        crate.Draw(ourShader);

        

        //skybox
        glDepthFunc(GL_LEQUAL);
        skyboxShader.use();
        view = glm::mat4(glm::mat3(view));
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        glBindVertexArray(mySkybox.VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


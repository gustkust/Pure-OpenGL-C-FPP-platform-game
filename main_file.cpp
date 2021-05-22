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
#include "building.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// window size
float SCR_WIDTH = 1024;
float SCR_HEIGHT = 768;

// time
float lastTime = 0.0;
float deltaTime = 0.0;

// camera
Camera myCam;


bool wPressed = false;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_A) myCam.setSpeedLeft(15 * deltaTime);
        if (key == GLFW_KEY_D) myCam.setSpeedRight(15 * deltaTime);
        if (key == GLFW_KEY_W) {
            wPressed = true;
            myCam.setSpeedForward(15 * deltaTime);
        }
        if (key == GLFW_KEY_S) myCam.setSpeedBackward(15 * deltaTime);
        if (key == GLFW_KEY_SPACE) myCam.jump(true);
        if (key == GLFW_KEY_C) myCam.newCrouch(true);
        if (key == GLFW_KEY_LEFT_SHIFT) {
            if (wPressed) {
                myCam.setSpeedForward(3 * 15 * deltaTime);
            }
        }
    }
    if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_A) myCam.setSpeedLeft(0);
        if (key == GLFW_KEY_D) myCam.setSpeedRight(0);
        if (key == GLFW_KEY_W)
        {
            wPressed = false;
            myCam.setSpeedForward(0);
        }
        if (key == GLFW_KEY_S) myCam.setSpeedBackward(0);
        if (key == GLFW_KEY_SPACE) myCam.jump(false);
        if (key == GLFW_KEY_C) myCam.newCrouch(false);
        if (key == GLFW_KEY_LEFT_SHIFT) {
            if (wPressed) {
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

    // creating window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Jumping on roofs!", NULL, NULL);

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
    Shader lightingShader("model.vs", "model.fs");
    Shader lightSourceShader("lightSource.vs", "lightSource.fs");

    // load model and create model object
    Model crate("resources/models/Crate/Crate1.obj");
    Model light("resources/models/Light/3d-model.obj");

    Building building1(glm::vec3(150.0f, -215.0f, 0.0f), 1);
    Building building2(glm::vec3(150.0f, -245.0f, 120.0f), 2);
    Building building3(glm::vec3(0.0f, -215.0f, 120.0f), 3);
    Building building4(glm::vec3(0.0f, -215.0f, 0.0f), 4);

    // load skybox
    Skybox citySkybox;

    // two static boxes
    Collision box1(glm::vec3(0.0f, -10.0f, 0.0f), glm::vec3(10.0f, 1.0f, 10.0f));
    Collision box3(glm::vec3(0.0f, -10.0f, -60.0f), glm::vec3(10.0f, 1.0f, 10.0f));
    
    Collision boxes[7];
    boxes[0] = box1;
    boxes[2] = box3;
    boxes[3] = building1.building_col;
    boxes[4] = building2.building_col;
    boxes[5] = building3.building_col;
    boxes[6] = building4.building_col;

    float boxPos = 0.0f; // additional possition of current box
    float boxPosChange = 0.15f; // change of boxPos per frame
    float boxPosRange = 80.0f; // range of boxPos
    // main loop

    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);
    while (!glfwWindowShouldClose(window)) {

        // moving box
        Collision box2(glm::vec3(boxPos, -10.0f, -30.0f), glm::vec3(10.0f, 1.0f, 10.0f), glm::vec3(boxPosChange, 0.0f, 0.0f));
        boxes[1] = box2;

        float thisTime = glfwGetTime();
        deltaTime = thisTime - lastTime;
        lastTime = thisTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myCam.positionChange(deltaTime, boxes);

        // shader constants
        float ambientValue = 0.3f;
        lightingShader.use();
        lightingShader.setVec3("viewPos", myCam.getPos());
        lightingShader.setFloat("material.shininess", 32.0f);
        lightingShader.setVec3("amb", ambientValue, ambientValue, ambientValue);

        // model, view and projection matrices setup
        glm::mat4 projection = glm::perspective(3.14f * 50.0f/180.0f, (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1f, 6000.0f);
        glm::mat4 view = myCam.getV();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);

        //building
        building1.draw(lightingShader, 0, lightSourceShader);
        building2.draw(lightingShader, 4, lightSourceShader);
        building3.draw(lightingShader, 8, lightSourceShader);
        building4.draw(lightingShader, 12, lightSourceShader);

        // boxes
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -10.0f, 0.0f));
        model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));
        lightingShader.setMat4("model", model);
        crate.Draw(lightingShader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -10.0f, -60.0f));
        model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));
        lightingShader.setMat4("model", model);
        crate.Draw(lightingShader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(boxPos, -10.0f, -30.0f)); // moving box
        model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));
        lightingShader.setMat4("model", model);
        crate.Draw(lightingShader);
        // update boxPos
        if (boxPos >= boxPosRange || boxPos <= -boxPosRange) boxPosChange *= -1;
        boxPos += boxPosChange;

        // skybox
        citySkybox.draw(view, projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


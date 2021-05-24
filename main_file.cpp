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

    // load platforms
    Model crate("resources/models/Crate/Crate1.obj");

    // load buildings
    Building building1(glm::vec3(0.0f, -215.0f, 0.0f), 1);
    Building building2(glm::vec3(150.0f, -215.0f, 0.0f), 2);
    Building building3(glm::vec3(150.0f, -245.0f, 150.0f), 3);
    Building building4(glm::vec3(150.0f, -275.0f, 350.0f), 4, glm::vec3(100.0f, 200.0f, 100.0f));
    Building building5(glm::vec3(200.0f, -215.0f, 550.0f), 1);
    Building building6(glm::vec3(0.0f, -215.0f, 525.0f), 2, glm::vec3(100.0f, 200.0f, 50.0f));
    Building building7(glm::vec3(-200.0f, -215.0f, 525.0f), 3);
    Building building8(glm::vec3(-200.0f, -245.0f, 325.0f), 4, glm::vec3(75.0f, 200.0f, 75.0f));
    Building building9(glm::vec3(-150.0f, -235.0f, 175.0f), 1);
    Building building10(glm::vec3(-125.0f, -225.0f, 0.0f), 3, glm::vec3(50.0f, 200.0f, 100.0f));
    // ^ it could be made better with loading only one building of each type and then coping it, instead of loading each builing separetly 

    // load skybox
    Skybox citySkybox;
    
    // set buildings collisions
    Collision boxes[12];
    boxes[0] = building1.building_col;
    boxes[1] = building2.building_col;
    boxes[2] = building3.building_col;
    boxes[3] = building4.building_col;
    boxes[4] = building5.building_col;
    boxes[6] = building6.building_col;
    boxes[7] = building7.building_col;
    boxes[9] = building8.building_col;
    boxes[10] = building9.building_col;
    boxes[11] = building10.building_col;

    // platforms movement
    float boxPos1 = 0.0f; // current additional possition of the box
    float boxPosChange1 = 0.8f; // change of boxPos per frame
    float boxPosRange1 = 80.0f; // range of boxPos

    float boxPos2 = 0.0f; // current additional possition of the box
    float boxPosChange2 = 0.6f; // change of boxPos per frame
    float boxPosRange2 = 100.0f; // range of boxPos

    // starting shader setup
    lightingShader.use();
    glUniform1i(glGetUniformLocation(lightingShader.ID, "value"), 0);

    // main loop
    while (!glfwWindowShouldClose(window)) {

        // moving boxes collisions setup
        Collision box1(glm::vec3(175.0f, boxPos1 - 20.0f, 475.0f), glm::vec3(10.0f, 1.0f, 10.0f), glm::vec3(0.0f, boxPosChange1, 0.0f));
        boxes[5] = box1;
        Collision box2(glm::vec3(boxPos2 - 200.0f, -20.0f, 435.0f), glm::vec3(10.0f, 1.0f, 10.0f), glm::vec3(boxPosChange2, 0.0f, 0.0f));
        boxes[8] = box2;

        // time passed calculation
        float thisTime = glfwGetTime();
        deltaTime = thisTime - lastTime;
        lastTime = thisTime;

        // clear buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // update camera position
        myCam.positionChange(deltaTime, boxes);

        // shader ambient and view matrix setup
        float ambientValue = 0.3f;
        lightingShader.use();
        glUniform3f(glGetUniformLocation(lightingShader.ID, "viewPos"), myCam.getPos().x, myCam.getPos().y, myCam.getPos().z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "amb"), ambientValue, ambientValue, ambientValue);

        // model, view and projection matrices setup
        glm::mat4 projection = glm::perspective(3.14f * 50.0f/180.0f, (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1f, 6000.0f);
        glm::mat4 view = myCam.getV();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glm::mat4 model = glm::mat4(1.0f);

        // draw buildings
        building1.draw(lightingShader, 0);
        building2.draw(lightingShader, 4);
        building3.draw(lightingShader, 8);
        building4.draw(lightingShader, 12);
        building5.draw(lightingShader, 16);
        building6.draw(lightingShader, 20);
        building7.draw(lightingShader, 24);
        building8.draw(lightingShader, 28);
        building9.draw(lightingShader, 32);
        building10.draw(lightingShader, 36);

        // draw box 1
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(175.0f, boxPos1 - 20.0f, 475.0f)); // moving box
        model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        crate.Draw(lightingShader);
        // update box 1 position
        if (boxPos1 >= boxPosRange1 || boxPos1 <= -boxPosRange1) boxPosChange1 *= -1;
        boxPos1 += boxPosChange1;

        // draw box 2
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(boxPos2 - 200.0f, -20.0f, 435.0f)); // moving box
        model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        crate.Draw(lightingShader);
        // update box 1 position
        if (boxPos2 >= boxPosRange2 || boxPos2 <= -boxPosRange2) boxPosChange2 *= -1;
        boxPos2 += boxPosChange2;

        // draw skybox
        citySkybox.draw(view, projection);

        // swap buffers and check for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}



// KeyCallback function should look something like this:
//void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//	if (action == GLFW_PRESS) {
//		if (key == GLFW_KEY_A) myCam.setSpeedLeft(0.06);
//		if (key == GLFW_KEY_D) myCam.setSpeedRight(0.06);
//		if (key == GLFW_KEY_W) myCam.setSpeedForward(0.06);
//		if (key == GLFW_KEY_S) myCam.setSpeedBackward(0.06);
//		if (key == GLFW_KEY_SPACE) myCam.jump(true);
//	}
//	if (action == GLFW_RELEASE) {
//		if (key == GLFW_KEY_A) myCam.setSpeedLeft(0);
//		if (key == GLFW_KEY_D) myCam.setSpeedRight(0);
//		if (key == GLFW_KEY_W) myCam.setSpeedForward(0);
//		if (key == GLFW_KEY_S) myCam.setSpeedBackward(0);
//		if (key == GLFW_KEY_SPACE) myCam.jump(false);
//	}
//}

// You will need global variable firstMouse = true and your MouseCallBack function should look like this:
//void mouseCallback(GLFWwindow* window, double xPos, double yPos)
//{
//	myCam.mouseMovement(xPos, yPos, firstMouse);
//	firstMouse = false;
//}

// In every frame you need to call positionChange method.

// Also you want to set these things:
//glfwSetKeyCallback(window, keyCallback);
//glfwSetCursorPosCallback(window, mouseCallback);
//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

// To get V you simply use getV method.


#ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stdio.h"
#include <iostream>
#include "collision.h"
using namespace std;


class camera {
private:
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 800.0f / 2.0;
	float lastY = 600.0 / 2.0;
	float fov = 45.0f;
	float cameraHeight = 5;

	float sensitivity = 0.1f;

	float gravitySpeed = -2.0f;
	float jumpSpeed = 0;
	float jumpHeight = 0;
	bool jumpUp = false;

	bool crouch;

	float speedLeft = 0;
	float speedRight = 0;
	float speedForward = 0;
	float speedBackward = 0;

public:
	void mouseMovement(float xPos, float yPos, bool firstMouse = false);
	void positionChange(float deltaTime, Collision box);
	void jump(bool keepJumping);
	void newCrouch(bool keepCrouch);

	void setSpeedLeft(float newValue);
	void setSpeedRight(float newValue);
	void setSpeedForward(float newValue);
	void setSpeedBackward(float newValue);
	void setLastX(float newValue);
	void setLastY(float newValue);

	glm::vec3 getPos();

	void changeSensitivity(float newValue);

	glm::mat4 getV();

	camera(glm::vec3 newPos = glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3 newFront = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 newUp = glm::vec3(0.0f, 1.0f, 0.0f),
		float newYaw = -90.0f, float newPitch = 0.0f,
		float newFov = 45.0f, float newSensitivity = 0.1f,
		float newLastX = 800.0f / 2.0, float newLastY = 600.0 / 2.0);
};


#endif
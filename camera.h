#ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stdio.h"
#include <iostream>
#include "collision.h"

using namespace std;


class Camera {
private:
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 800.0f / 2.0;
	float lastY = 600.0 / 2.0;
	float fov = 45.0f;
	float cameraHeight = 7;

	float sensitivity = 0.1f;

	float gravitySpeed = -2.0f;
	float jumpSpeed = 0;
	float jumpHeight = 0;
	bool jumpUp = false;
	bool fallDown = false;

	bool firstFrame = true;

	bool crouch;

	float speedLeft = 0;
	float speedRight = 0;
	float speedForward = 0;
	float speedBackward = 0;

public:
	void mouseMovement(float xPos, float yPos, bool firstMouse = false);
	void positionChange(float deltaTime, Collision boxes[12]);
	void jump(bool keepJumping);
	void newCrouch(bool keepCrouch);

	void setSpeedLeft(float newValue);
	void setSpeedRight(float newValue);
	void setSpeedForward(float newValue);
	void setSpeedBackward(float newValue);
	void setLastX(float newValue);
	void setLastY(float newValue);

	glm::vec3 getPos();
	glm::vec3 getFront();

	void changeSensitivity(float newValue);

	glm::mat4 getV();

	Camera(glm::vec3 newPos = glm::vec3(0.0f, 2.0f, 3.0f),
		glm::vec3 newFront = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 newUp = glm::vec3(0.0f, 1.0f, 0.0f),
		float newYaw = -90.0f, float newPitch = 0.0f,
		float newFov = 45.0f, float newSensitivity = 0.1f,
		float newLastX = 800.0f / 2.0, float newLastY = 600.0 / 2.0);
};


#endif
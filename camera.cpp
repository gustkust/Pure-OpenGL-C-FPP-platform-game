#include "camera.h"


void camera::mouseMovement(float xPos, float yPos, bool firstMouse) {
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);
}


void camera::positionChange()
{
	pos += speedForward * front;
	pos -= speedBackward * front;
	pos -= glm::normalize(glm::cross(front, up)) * speedLeft;
	pos += glm::normalize(glm::cross(front, up)) * speedRight;

	if (jumpUp && jumpHeight < 1) {
		jumpHeight += 0.04;
		if (jumpHeight >= 1) {
			jumpUp = false;
			jumpDown = true;
		}
	}
	else if (jumpDown && jumpHeight > 0) {
		jumpHeight -= 0.04;
		if (jumpHeight <= 0) jumpDown = false;
	}
}


void camera::newJump() {
	if (!jumpDown) jumpUp = true;
}


void camera::setSpeedLeft(float newValue) {
	speedLeft = newValue;
}


void camera::setSpeedRight(float newValue) {
	speedRight = newValue;
}


void camera::setSpeedForward(float newValue) {
	speedForward = newValue;
}


void camera::setSpeedBackward(float newValue) {
	speedBackward = newValue;
}


void camera::setLastX(float newValue) {
	lastX = newValue;
}


void camera::setLastY(float newValue) {
	lastY = newValue;
}


void camera::changeSensitivity(float newValue) {
	sensitivity = newValue;
}


glm::mat4 camera::getV() {
	//return glm::lookAt(pos, pos + front, up);

	// To get FPS camera use instead:
	return glm::lookAt(glm::vec3(pos.x, 2 + jumpHeight, pos.z), glm::vec3(pos.x, 2 + jumpHeight, pos.z) + front, up);
}


camera::camera(glm::vec3 newPos, glm::vec3 newFront, glm::vec3 newUp,
	float newYaw, float newPitch, float newFov,
	float newSensitivity, float newLastX, float newLastY) {
	pos = newPos;
	front = newFront;
	up = newUp;
	yaw = newYaw;
	pitch = newPitch;
	fov = newFov;
	sensitivity = newSensitivity;
	lastX = newLastX;
	lastY = newLastY;
}
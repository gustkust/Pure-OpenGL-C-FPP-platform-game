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


void camera::positionChange(float deltaTime)
{
	pos += speedForward * front;
	pos -= speedBackward * front;
	pos -= glm::normalize(glm::cross(front, up)) * speedLeft;
	pos += glm::normalize(glm::cross(front, up)) * speedRight;

	jumpHeight += 5 * deltaTime * jumpSpeed;
	jumpSpeed += 5 * deltaTime * gravitySpeed;
	if (jumpHeight <= 0) {
		jumpHeight = 0;
		jumpUp = false;
	}
}


void camera::jump(bool keepJumping) {
	if (keepJumping && !jumpUp) {
		jumpSpeed = 7.0;
		jumpUp = true;
	}
	else if (!keepJumping) jumpSpeed = 0;
}


void camera::newCrouch(bool keepCrouch) {
	if (keepCrouch) crouch = true;
	else if (!keepCrouch && crouch) crouch = false;
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
	// return glm::lookAt(pos, pos + front, up);

	// To get FPS camera use instead:
	cout << pos.x << " " << 2 + jumpHeight << " " << pos.z << "\n";
	if (!crouch) return glm::lookAt(glm::vec3(pos.x, cameraHeight + jumpHeight, pos.z), glm::vec3(pos.x, cameraHeight + jumpHeight, pos.z) + front, up);
	return glm::lookAt(glm::vec3(pos.x, cameraHeight + jumpHeight - 1, pos.z), glm::vec3(pos.x, cameraHeight + jumpHeight - 1, pos.z) + front, up);
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
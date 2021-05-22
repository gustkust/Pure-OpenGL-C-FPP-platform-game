#include "camera.h"


void Camera::mouseMovement(float xPos, float yPos, bool firstMouse) {
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


void Camera::positionChange(float deltaTime, Collision boxes[7])
{
	pos += speedForward * front;
	pos -= speedBackward * front;
	pos -= glm::normalize(glm::cross(front, up)) * speedLeft;
	pos += glm::normalize(glm::cross(front, up)) * speedRight;

	if (jumpHeight <= -400.0f) {
		pos = glm::vec3(0.0f, 0.0f, 3.0f);
		jumpHeight = 0.0f;
	}

	jumpHeight += 5 * deltaTime * jumpSpeed;
	jumpSpeed += 5 * deltaTime * gravitySpeed;
	for (int i = 0; i < 7; i++) {
		if (boxes[i].checkCollision(pos)) {
			if (jumpHeight <= boxes[i].sector[1][1] && jumpHeight >= boxes[i].sector[1][1] - 15) {
				jumpHeight = boxes[i].sector[1][1];
				jumpUp = false;
				pos += boxes[i].posChange;
			}
		}
	}
}


void Camera::jump(bool keepJumping) {
	if (keepJumping && !jumpUp) {
		jumpSpeed = 7.0;
		jumpUp = true;
		fallDown = false;
	}
	else if (!keepJumping && !fallDown) {
		jumpSpeed = 0;
		fallDown = true;
	}
}


void Camera::newCrouch(bool keepCrouch) {
	if (keepCrouch) crouch = true;
	else if (!keepCrouch && crouch) crouch = false;
}


void Camera::setSpeedLeft(float newValue) {
	speedLeft = newValue;
}


void Camera::setSpeedRight(float newValue) {
	speedRight = newValue;
}


void Camera::setSpeedForward(float newValue) {
	speedForward = newValue;
}


void Camera::setSpeedBackward(float newValue) {
	speedBackward = newValue;
}


void Camera::setLastX(float newValue) {
	lastX = newValue;
}


void Camera::setLastY(float newValue) {
	lastY = newValue;
}


void Camera::changeSensitivity(float newValue) {
	sensitivity = newValue;
}


glm::mat4 Camera::getV() {
	cout << pos.x << " " << 2 + jumpHeight << " " << pos.z << "\n";
	//return glm::lookAt(pos, pos + front, up);
	// To get FPS camera use instead:
	if (!crouch) return glm::lookAt(glm::vec3(pos.x, cameraHeight + jumpHeight, pos.z), glm::vec3(pos.x, cameraHeight + jumpHeight, pos.z) + front, up);
	return glm::lookAt(glm::vec3(pos.x, cameraHeight + jumpHeight - 1, pos.z), glm::vec3(pos.x, cameraHeight + jumpHeight - 1, pos.z) + front, up);
}


Camera::Camera(glm::vec3 newPos, glm::vec3 newFront, glm::vec3 newUp,
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

glm::vec3 Camera::getPos() {
	return pos;
}

glm::vec3 Camera::getFront() {
	return front;
}
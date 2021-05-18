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


void camera::positionChange(float deltaTime, Collision boxes[7])
{
	pos += speedForward * front;
	pos -= speedBackward * front;
	pos -= glm::normalize(glm::cross(front, up)) * speedLeft;
	pos += glm::normalize(glm::cross(front, up)) * speedRight;

	if (jumpHeight <= -1000.0f) {
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


void camera::jump(bool keepJumping) {
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
	cout << pos.x << " " << 2 + jumpHeight << " " << pos.z << "\n";
	//return glm::lookAt(pos, pos + front, up);
	// To get FPS camera use instead:
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

glm::vec3 camera::getPos() {
	return pos;
}
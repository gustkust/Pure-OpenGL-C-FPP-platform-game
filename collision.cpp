
#include "collision.h"


Collision::Collision(glm::vec3 position, glm::vec3 size, glm::vec3 posChange) {
	sector[0][0] = position[0] - size[0];
	sector[0][1] = position[0] + size[0];
	sector[1][0] = position[1] - size[1];
	sector[1][1] = position[1] + size[1];
	sector[2][0] = position[2] - size[2];
	sector[2][1] = position[2] + size[2];
	this->posChange = posChange;
}


bool Collision::checkCollision(glm::vec3 cameraPosition) {
	if ((cameraPosition[0] >= sector[0][0] && cameraPosition[0] <= sector[0][1]) &&
		(cameraPosition[2] >= sector[2][0] && cameraPosition[2] <= sector[2][1])) {
		return true;
	}
	return false;
}


Collision::Collision() {}
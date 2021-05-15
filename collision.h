#ifndef COLLISION_H
#define COLLISION_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Collision {
public:
	Collision();
	Collision(glm::vec3 position, glm::vec3 size, glm::vec3 posChange = glm::vec3(0.0f, 0.0f, 0.0f));
	float sector[3][2];
	bool checkCollision(glm::vec3 cameraPosition);
	glm::vec3 posChange;
};
#endif
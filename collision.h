#ifndef COLLISION_H
#define COLLISION_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Collision {
public:
	Collision(glm::vec3 position, glm::vec3 size);
	float sector[3][2];
	bool checkCollision(glm::vec3 cameraPosition);
};
#endif
#ifndef BUILDING_H
#define BUILDING_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "model.h"
#include "collision.h"
#include "shader.h"

class Building {
	private:
		Model building;
		Model vents;
		Model solar_panel;
		glm::vec3 pos;
		glm::vec3 size;
	public:
		Collision building_col;
		Building(glm::vec3 pos, glm::vec3 size = glm::vec3(50.0f, 200.0f, 50.0f));
		void draw(Shader ourShader);
};

#endif

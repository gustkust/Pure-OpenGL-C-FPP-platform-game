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
	public:
		Collision building_col;
		Building(glm::vec3 pos);
		void draw(Shader ourShader);
};

#endif

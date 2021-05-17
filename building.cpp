#include "building.h"

Building::Building(glm::vec3 pos, glm::vec3 size) {
	Model tmp1("resources/models/building/building.obj");
	this->building = tmp1;
	Model tmp2("resources/models/vents/3d-model.obj");
	this->vents = tmp2;
	Model tmp3("resources/models/solar_panel/3d-model.obj");
	this->solar_panel = tmp3;
	Collision tmp4(pos, size);
	this->building_col = tmp4;
	this->pos = pos;
	this->size = size;
}

void Building::draw(Shader ourShader) {
	// building
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, size);
	model = glm::rotate(model, 270.0f * 3.14f / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	ourShader.setMat4("model", model);
	building.Draw(ourShader);

	// vents
	model = glm::mat4(1.0f);
	model = glm::translate(model, pos + size + glm::vec3(-45.0f, -2.0f, -25.0f));
	model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
	ourShader.setMat4("model", model);
	vents.Draw(ourShader);

	// solar panel
	model = glm::mat4(1.0f);
	model = glm::translate(model, pos - size + glm::vec3(15.0f, 400.0f, 15.0f));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	ourShader.setMat4("model", model);
	solar_panel.Draw(ourShader);

	model = glm::mat4(1.0f);
	model = glm::translate(model, pos - size + glm::vec3(32.0f, 400.0f, 15.0f));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	ourShader.setMat4("model", model);
	solar_panel.Draw(ourShader);

	model = glm::mat4(1.0f);
	model = glm::translate(model, pos - size + glm::vec3(49.0f, 400.0f, 15.0f));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	ourShader.setMat4("model", model);
	solar_panel.Draw(ourShader);
}
#include "building.h"

Building::Building(glm::vec3 pos) {
	Model tmp1("resources/models/building/building.obj");
	this->building = tmp1;
	//Model tmp2("resources/models/vents/3d-model.obj");
	//this->building = tmp2;
	//Model tmp3("resources/models/solar_panel/3d-model.obj");
	//this->building = tmp3;
	Collision tmp4(pos, glm::vec3(200.0f, 200.0f, 200.0f));
	this->building_col = tmp4;
	this->pos = pos;
}

void Building::draw(Shader ourShader) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(240.0f, -215.0f, 0.0f));
	model = glm::scale(model, glm::vec3(200.0f, 200.0f, 200.0f));
	model = glm::rotate(model, 270.0f * 3.14f / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	ourShader.setMat4("model", model);
	building.Draw(ourShader);
}
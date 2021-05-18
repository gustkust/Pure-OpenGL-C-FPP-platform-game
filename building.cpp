#include "building.h"

Building::Building(glm::vec3 pos, int type, glm::vec3 size) {
	this->type = type;
	this->pos = pos;
	this->size = size;
	Collision tmpCol(pos, size);
	this->building_col = tmpCol;
	if (type == 1) {
		Model tmp1("resources/models/building/building.obj");
		this->model1 = tmp1;
		Model tmp2("resources/models/vents/3d-model.obj");
		this->model2 = tmp2;
		Model tmp3("resources/models/solar_panel/3d-model.obj");
		this->model3 = tmp3;
	}
	else if (type == 2) {
		Model tmp1("resources/models/building/building.obj");
		this->model1 = tmp1;
		Model tmp2("resources/models/helipad/3d-model.obj");
		this->model2 = tmp2;
		Model tmp3("resources/models/helicopter/uploads_files_2739645_HelicopterOBJ.obj");
		this->model3 = tmp3;
	}
}

void Building::draw(Shader ourShader) {
	if (type == 1) {
		// building
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		model = glm::scale(model, size);
		model = glm::rotate(model, 270.0f * 3.14f / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);
		model1.Draw(ourShader);

		// vents
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos + size + glm::vec3(-45.0f, -2.0f, -25.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		ourShader.setMat4("model", model);
		model2.Draw(ourShader);

		// solar panel
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos - size + glm::vec3(15.0f, 400.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		ourShader.setMat4("model", model);
		model3.Draw(ourShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, pos - size + glm::vec3(32.0f, 400.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		ourShader.setMat4("model", model);
		model3.Draw(ourShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, pos - size + glm::vec3(49.0f, 400.0f, 15.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		ourShader.setMat4("model", model);
		model3.Draw(ourShader);
	}
	else if (type == 2) {
		// building
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		model = glm::scale(model, size);
		model = glm::rotate(model, 270.0f * 3.14f / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);
		model1.Draw(ourShader);

		// helipad
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos + glm::vec3(0.0f, 190.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		ourShader.setMat4("model", model);
		model2.Draw(ourShader);

		// helicopter
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos + glm::vec3(0.0f, 211.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		ourShader.setMat4("model", model);
		model3.Draw(ourShader);
	}
}
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
		Model tmp4("resources/models/Light/3d-model.obj");
		this->light = tmp4;
	}
	else if (type == 2) {
		Model tmp1("resources/models/building2/building.obj");
		this->model1 = tmp1;
		Model tmp2("resources/models/helipad/3d-model.obj");
		this->model2 = tmp2;
		Model tmp3("resources/models/helicopter/uploads_files_2739645_HelicopterOBJ.obj");
		this->model3 = tmp3;
		Model tmp4("resources/models/Light/3d-model.obj");
		this->light = tmp4;
	}
	else if (type == 3) {
		Model tmp1("resources/models/building3/building.obj");
		this->model1 = tmp1;
		Model tmp2("resources/models/Sculpture/Musa_highpoly.obj");
		this->model2 = tmp2;
		Model tmp3("resources/models/Palm/kkviz dypsis lutescens_01.obj");
		this->model3 = tmp3;
		Model tmp4("resources/models/Plant/uploads_files_2749739_A1.obj");
		this->model4 = tmp4;
		Model tmp5("resources/models/Light/3d-model.obj");
		this->light = tmp5;
	}
	else if (type == 4) {
		Model tmp1("resources/models/building4/building.obj");
		this->model1 = tmp1;
		Model tmp2("resources/models/Dumpster/uploads_files_2257883_dumpster_obj.obj");
		this->model2 = tmp2;
		Model tmp3("resources/models/Bucket/Bucket3.obj");
		this->model3 = tmp3;
		Model tmp4("resources/models/Arm/Robotic Arm.obj");
		this->model4 = tmp4;
		Model tmp5("resources/models/Light/3d-model.obj");
		this->light = tmp5;
	}	 
}

void Building::draw(Shader ourShader) {
	// building
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, size);
	model = glm::rotate(model, 270.0f * 3.14f / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	ourShader.setMat4("model", model);
	model1.Draw(ourShader);

	model = glm::mat4(1.0f);
	model = glm::translate(model, pos - size + glm::vec3(4.0f, 400.0f, 3.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	model = glm::rotate(model, 270.0f * 3.14f / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 135.0f * 3.14f / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	ourShader.setMat4("model", model);
	light.Draw(ourShader);

	model = glm::mat4(1.0f);
	model = glm::translate(model, pos + size + glm::vec3(-4.0f, 1.0f, -3.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	model = glm::rotate(model, 270.0f * 3.14f / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 315.0f * 3.14f / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	ourShader.setMat4("model", model);
	light.Draw(ourShader);

	model = glm::mat4(1.0f);
	model = glm::translate(model, pos + glm::vec3(-size[2] + 4.5f, 201.0f, size[2] - 3.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	model = glm::rotate(model, 270.0f * 3.14f / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 45.0f * 3.14f / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	ourShader.setMat4("model", model);
	light.Draw(ourShader);

	model = glm::mat4(1.0f);
	model = glm::translate(model, pos + glm::vec3(size[2] - 4.5f, 200.0f, -size[2] + 3.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	model = glm::rotate(model, 270.0f * 3.14f / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 225.0f * 3.14f / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	ourShader.setMat4("model", model);
	light.Draw(ourShader);

	if (type == 1) {
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
	else if (type == 3) {
		// sculpture
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos + glm::vec3(0.0f, 200.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		ourShader.setMat4("model", model);
		model2.Draw(ourShader);

		// palms
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos - size + glm::vec3(15.0f, 400.0f, 15.0f)); // -85,-85
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		ourShader.setMat4("model", model);
		model3.Draw(ourShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, pos + size + glm::vec3(-15.0f, 0.0f, -15.0f)); // 85, 85
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		ourShader.setMat4("model", model);
		model3.Draw(ourShader);

		// plants
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos + glm::vec3(-size[2]+15.0f, 200.0f, size[2]-15.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		ourShader.setMat4("model", model);
		model4.Draw(ourShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, pos + glm::vec3(size[2] - 15.0f, 200.0f, -size[2] + 15.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		ourShader.setMat4("model", model);
		model4.Draw(ourShader);
	}
	else if (type == 4) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos + glm::vec3(size[2] - 15.0f, 200.0f, -size[2] + 15.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		ourShader.setMat4("model", model);
		model2.Draw(ourShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, pos + glm::vec3(size[2] - 25.0f, 201.0f, -size[2] + 15.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		ourShader.setMat4("model", model);
		model3.Draw(ourShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, pos + glm::vec3(-size[2] + 15.0f, 201.0f, size[2] - 15.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		ourShader.setMat4("model", model);
		model4.Draw(ourShader);
	}
}
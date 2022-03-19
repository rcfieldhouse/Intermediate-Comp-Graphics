#include "Gameplay/Components/RotatingBehaviour.h"

#include "Gameplay/GameObject.h"

#include "Utils/ImGuiHelper.h"
#include "Utils/JsonGlmHelpers.h"

void RotatingBehaviour::Update(float deltaTime) {
	if (bounceDirection> 6) {
		bounceHeight = glm::vec3(0.0f, 0.0f, 10.0f);
	}
	timer += deltaTime;
	if (bounceDirection == 2) {
		moveVector = glm::vec3(-5.0f, 0.0f, 0.0f);
	}
	if (bounceDirection == 3) {
		moveVector = glm::vec3(0.0f, 5.0f, 0.0f);
	}
	if (bounceDirection == 4) {
		moveVector = glm::vec3(5.0f, 0.0f, 0.0f);
	}
	if (bounceDirection == 5) {
		moveVector = glm::vec3(0.0f, -5.0f, 0.0f);
	}
	if (timer <= bounceSpeed) {
		GetGameObject()->SetPostion(GetGameObject()->GetPosition() + bounceHeight * deltaTime * (bounceSpeed -timer)+moveVector*deltaTime);
	}
	else {
		GetGameObject()->SetPostion(GetGameObject()->GetPosition() - bounceHeight * deltaTime * (timer- bounceSpeed)+ moveVector * deltaTime);
	}
	if (timer > 2* bounceSpeed) {
		timer -= 2* bounceSpeed;
		if (bounceDirection < 5) {
			bounceDirection++;
		}
		else if (bounceDirection == 5) {
			bounceDirection = 2;
		}
		GetGameObject()->SetPostion(glm::vec3(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y, 1.0f));
	}
	GetGameObject()->SetRotation(GetGameObject()->GetRotationEuler() + bounceHeight * deltaTime*6.0f);
}
void RotatingBehaviour::setDirection(float dir) {
	bounceDirection = dir;
}
void RotatingBehaviour::RenderImGui() {
	LABEL_LEFT(ImGui::DragFloat3, "Speed", &bounceHeight.x);
}

nlohmann::json RotatingBehaviour::ToJson() const {
	return {
		{ "speed", bounceHeight }
	};
}

RotatingBehaviour::Sptr RotatingBehaviour::FromJson(const nlohmann::json& data) {
	RotatingBehaviour::Sptr result = std::make_shared<RotatingBehaviour>();
	result->bounceHeight = JsonGet(data, "speed", result->bounceHeight);
	return result;
}

#pragma once
#include "IComponent.h"

/// <summary>
/// Showcases a very simple behaviour that rotates the parent gameobject at a fixed rate over time
/// </summary>
class RotatingBehaviour : public Gameplay::IComponent {
private:
	
	float timer = 0.0f;
	float bounceSpeed = 0.5f;
	float bounceDirection=0;
	glm::vec3 moveVector=glm::vec3(0.0f,0.0f,0.0f);
public:
	typedef std::shared_ptr<RotatingBehaviour> Sptr;
	RotatingBehaviour() = default;
	glm::vec3 bounceHeight = glm::vec3(0.0f, 0.0f, 30.0f);

	void setDirection(float dir);
	virtual void Update(float deltaTime) override;

	virtual void RenderImGui() override;

	virtual nlohmann::json ToJson() const override;
	static RotatingBehaviour::Sptr FromJson(const nlohmann::json& data);

	MAKE_TYPENAME(RotatingBehaviour);
};


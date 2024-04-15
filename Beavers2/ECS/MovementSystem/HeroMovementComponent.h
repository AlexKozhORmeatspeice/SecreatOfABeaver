#pragma once
#include "Components.h"
#include "Render.h"
#include "ECSFunc.h"

class HeroMovementComponent : public Component
{
private:
	std::shared_ptr<PositionComponent> pos;
	bool canMove = false;

	glm::vec3 targetPoint;
	float speed;
public:
	HeroMovementComponent();
	HeroMovementComponent(float nowSpeed);

	void update() override;
	void init() override;

private:
	void Move();
	void SetTarget();
};
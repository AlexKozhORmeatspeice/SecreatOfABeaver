#pragma once
#include "Components.h"

class EnemyMovement : public Component
{
private:
	std::shared_ptr<PositionComponent> heroPos;
	std::shared_ptr<PositionComponent> pos;

	std::shared_ptr<BoxCollider> collider;

	Entity* checkCircle;
	std::shared_ptr<PositionComponent> checkCirclePos;

	glm::vec3 viewDir;
	float viewDist;

	float speed;
public:
	EnemyMovement();
	EnemyMovement(float nowViewDist, float nowSpeed);

	void update() override;
	void init() override;

private:
	void Move();
};
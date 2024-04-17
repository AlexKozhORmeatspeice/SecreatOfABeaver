#pragma once
#include "Components.h"

class Enemy : public Component
{
private:
	std::shared_ptr<PositionComponent> heroPos;
	std::shared_ptr<PositionComponent> pos;

	std::shared_ptr<BoxCollider> collider;

	glm::vec3 viewDir;
	float viewDist;
	float viewAngle;

	float speed;
public:
	Enemy();
	Enemy(float nowViewDist, float nowViewAngle, float nowSpeed);

	void update() override;
	void init() override;

private:
	void Move();
};
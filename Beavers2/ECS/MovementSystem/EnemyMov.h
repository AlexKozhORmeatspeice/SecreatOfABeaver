#pragma once
#include "Components.h"

class EnemyMov : public Component
{
private:
	Enemy* enemy;

	Transform* heroPos;
	Transform* pos;

	BoxCollider* collider;

	Entity* checkCircle;
	Transform* checkCirclePos;

	glm::vec3 viewDir;
	
	Stamina* stamina;
	unsigned int moveCost;
	float viewDist;

	float speed;
public:
	EnemyMov();
	EnemyMov(float nowViewDist, unsigned int nowMoveCost);

	void update() override;
	void init() override;

	~EnemyMov();
private:
	void Move();
};
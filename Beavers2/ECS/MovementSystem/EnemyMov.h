#pragma once
#include "Components.h"

class EnemyMov : public Component
{
private:
	std::shared_ptr<PositionComponent> heroPos;
	std::shared_ptr<PositionComponent> pos;

	std::shared_ptr<BoxCollider> collider;

	Entity* checkCircle;
	std::shared_ptr<PositionComponent> checkCirclePos;

	glm::vec3 viewDir;
	
	std::shared_ptr<Stamina> stamina;
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
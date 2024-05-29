#pragma once
#include "ECS.h"
#include "EnemyAttack.h"
#include "BoxCollider.h"
#include "Stamina.h"
#include "Enemy.h"
#include "Render.h"

class EnemyMov : public Component
{
private:
	EnemyAttack* attackSys;
	Enemy* enemy;

	Transform* pos;

	BoxCollider* collider;

	glm::vec3 viewDir;
	
	Stamina* stamina;
	unsigned int moveCost;

	float speed;

	float wayWalked;
	float viewDist;
public:
	EnemyMov();
	EnemyMov(unsigned int nowMoveCost);

	void update() override;
	void init() override;

	~EnemyMov();
private:
	
	void Move();
};
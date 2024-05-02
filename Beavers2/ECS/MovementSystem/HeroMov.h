#pragma once
#include "ECS.h"

#include "StepSystemManager.h"
#include "Hero.h"
#include "HeroMov.h"

#include "Stamina.h"
#include "PositionComponent.h"

#include "Render.h"
#include "ECSFunc.h"

class HeroMov : public Component
{
private:
	Hero* heroComp;

	Stamina* stamina;
	Transform* pos;
	
	bool canMove = false;

	glm::vec3 targetPoint;
	
	float speed;
	unsigned int moveCost;

	bool isMoving = false;

	Circle* circle;
	Transform* circlePos;
public:
	HeroMov();
	HeroMov(unsigned int nowMoveCost);

	void update() override;
	void draw() override;
	void init() override;
	
	~HeroMov();
private:
	void SetOtherNotChoosed(HeroMov* exceptComp);

	void Move();
	void SetTarget();

	bool CanMove(glm::vec3 pos1, glm::vec3 pos2, unsigned int nowMovCost);
	void UseStaminaToMove(glm::vec3 pos1, glm::vec3 pos2, unsigned int nowMovCost);
};
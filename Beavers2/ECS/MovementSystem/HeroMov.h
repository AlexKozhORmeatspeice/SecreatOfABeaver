#pragma once
#include "Components.h"
#include "Render.h"
#include "ECSFunc.h"


class HeroMov : public Component
{
private:
	static std::vector<HeroMov*> movComps;

	std::shared_ptr<Stamina> stamina;
	std::shared_ptr<PositionComponent> pos;
	
	bool canMove = false;
	bool isChoosed = false;

	glm::vec3 targetPoint;
	
	float speed;
	unsigned int moveCost;

	bool isMoving = false;

	Entity* circleMoveEntity;
	std::shared_ptr<Circle> circle;
	std::shared_ptr<PositionComponent> circlePos;
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
};
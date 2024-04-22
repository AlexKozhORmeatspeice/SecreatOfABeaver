#pragma once
#include "Components.h"
#include "Render.h"
#include "ECSFunc.h"

class HeroMovementComponent : public Component
{
private:
	static std::vector<HeroMovementComponent*> movComps;
	std::shared_ptr<PositionComponent> pos;
	bool canMove = false;

	glm::vec3 targetPoint;
	float speed;
public:
	HeroMovementComponent();
	HeroMovementComponent(float nowSpeed);

	void update() override;
	void init() override;
	
	~HeroMovementComponent();
private:
	void SetOtherCantMove(HeroMovementComponent* exceptComp);

	void Move();
	void SetTarget();
};
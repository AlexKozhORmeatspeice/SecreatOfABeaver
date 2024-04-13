#pragma once
#include "Components.h"

class HeroMovementComponent : public Component
{
private:
	std::shared_ptr<PositionComponent> pos;
	bool canMove = false;
public:

	HeroMovementComponent();

	void update() override;
	void init() override;
};
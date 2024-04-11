#pragma once
#include "Components.h"

class MovementComponent : public Component
{
private:
	bool changedHor;
	bool changedVer;

	int lastActiveHor;
	int lastActiveVer;

	float speed;
	std::shared_ptr<PostitionComponent> pos;
public:

	MovementComponent();
	MovementComponent(float nowSpeed);
	void init() override;
	void update() override;
};

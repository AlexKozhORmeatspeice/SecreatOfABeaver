#pragma once
#include "Components.h"

class MovementComponent : public Component
{
private:
	bool changedHor = false;
	bool changedVer = false;

	int lastActiveHor = 0;
	int lastActiveVer = 0;

	float speed;
	std::shared_ptr<PostitionComponent> pos;
public:

	MovementComponent();
	MovementComponent(float nowSpeed);
	void init() override;
	void update() override;

	~MovementComponent();
};

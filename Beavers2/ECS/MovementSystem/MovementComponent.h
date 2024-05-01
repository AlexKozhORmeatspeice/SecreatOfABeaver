#pragma once
#include "Components.h"

class MovementComponent : public Component
{
private:
	bool changedHor = false;
	bool changedVer = false;
	bool canMove = true;


	int lastActiveHor = 0;
	int lastActiveVer = 0;


	float speed;
	PositionComponent* pos;
public:

	MovementComponent();
	MovementComponent(float nowSpeed);
	void init() override;
	void update() override;

	void StopMove();
	void StartMove();

	~MovementComponent();
};

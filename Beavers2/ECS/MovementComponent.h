#pragma once
#include "Components.h"

class MovementComponent : public Component
{
private:
	float speed;
	std::shared_ptr<PostitionComponent> pos;
public:

	MovementComponent();
	MovementComponent(float nowSpeed);
	void init() override;
	void update() override;
};

#include "HeroMovementComponent.h"



HeroMovementComponent::HeroMovementComponent()
{
	pos = entity->GetComponent<PositionComponent>();
}

void HeroMovementComponent::update()
{
	int xpos, ypos;
}

void HeroMovementComponent::init()
{
	//
}
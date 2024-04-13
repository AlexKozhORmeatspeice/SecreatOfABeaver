#include "HeroMovementComponent.h"



HeroMovementComponent::HeroMovementComponent()
{
	pos = entity->GetComponent<PostitionComponent>();
}

void HeroMovementComponent::update()
{
	int xpos, ypos;
}

void HeroMovementComponent::init()
{
	//
}
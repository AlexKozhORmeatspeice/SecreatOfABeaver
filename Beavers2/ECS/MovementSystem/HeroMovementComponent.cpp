#include "HeroMovementComponent.h"


std::vector<HeroMovementComponent*> HeroMovementComponent::movComps;

HeroMovementComponent::HeroMovementComponent()
{
	movComps.push_back(this);
	speed = 1.0f;
}
HeroMovementComponent::HeroMovementComponent(float nowSpeed)
{
	movComps.push_back(this);
	speed = nowSpeed;
}

void HeroMovementComponent::init()
{
	pos = entity->GetComponent<PositionComponent>();	
}


void HeroMovementComponent::update()
{
	int mouseLeftState = GLFWGetKeyMouseState(GLFW_MOUSE_BUTTON_LEFT);
	int mouseRightState = GLFWGetKeyMouseState(GLFW_MOUSE_BUTTON_RIGHT);
	

	for (auto* coll : movComps)
	{
		if (mouseLeftState == GLFW_PRESS && Coursor::GetCollision<BoxCollider>(coll->entity))
		{
			coll->canMove = true;
			SetOtherCantMove(coll);

			//TODO: draw circle move if active
			
			break;
		}
	}
	

	if (mouseRightState == GLFW_PRESS || !canMove)
	{
		canMove = false;
		//TODO: erase circle move if unactive
	}

	if (canMove && mouseLeftState == GLFW_PRESS && !Coursor::GetCollision<BoxCollider>(entity))
	{
		SetTarget();
	}

	if (canMove)
		Move();
	else
		targetPoint = pos->GetPos();
}

void HeroMovementComponent::Move()
{
	if (glm::distance(targetPoint, pos->GetPos()) <= speed)
		return;

	glm::vec3 dir = targetPoint - pos->GetPos();
	dir /= glm::length(dir);

	pos->SetPos(pos->GetPos() + dir*speed);
}

void HeroMovementComponent::SetTarget()
{
	targetPoint = Coursor::GetMousePos();

}

void HeroMovementComponent::SetOtherCantMove(HeroMovementComponent* exceptComp)
{
	for (auto& comp : movComps)
	{
		if (comp == exceptComp)
			continue;

		comp->canMove = false;
	}

}

HeroMovementComponent::~HeroMovementComponent()
{
	auto it = std::find(movComps.begin(), movComps.end(), this);
	if (it != movComps.end())
		movComps.erase(it);
}
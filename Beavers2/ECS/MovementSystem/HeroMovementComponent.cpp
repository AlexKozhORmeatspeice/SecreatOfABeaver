#include "HeroMovementComponent.h"

HeroMovementComponent::HeroMovementComponent()
{
	speed = 1.0f;
}
HeroMovementComponent::HeroMovementComponent(float nowSpeed)
{
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
	
	if (mouseLeftState == GLFW_PRESS && Coursor::GetCollision(entity))
	{
		canMove = true;
		std::shared_ptr<SpriteComponent> spr = entity->GetComponent<SpriteComponent>();
		if (spr)
		{
			spr->SetNewColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
	//TODO: erase sprites here. it's just for test
	if (mouseRightState == GLFW_PRESS)
	{
		canMove = false;
		std::shared_ptr<SpriteComponent> spr = entity->GetComponent<SpriteComponent>();
		if (spr)
		{
			spr->SetNewColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		}
	}

	if (canMove && mouseLeftState == GLFW_PRESS)
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
	if (glm::distance(targetPoint, pos->GetPos()) < 0.05f)
		return;

	glm::vec3 dir = targetPoint - pos->GetPos();
	dir /= glm::length(dir);

	pos->SetPos(pos->GetPos() + dir*speed);
}

void HeroMovementComponent::SetTarget()
{
	targetPoint = Coursor::GetMousePos();

}
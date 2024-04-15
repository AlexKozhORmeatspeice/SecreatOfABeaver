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
	glm::vec4 mousePos4 = glm::vec4(Coursor::GetMousePos().x, Coursor::GetMousePos().y, Coursor::GetMousePos().z, 1);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), -CamComponent::GetPos());
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(mousePos4.x, mousePos4.y, mousePos4.z));
	glm::mat4 m_VP = view * model;

	mousePos4 = m_VP * mousePos4;
	targetPoint = glm::vec3(mousePos4.x, mousePos4.y, mousePos4.w);

}
#include "MovementComponent.h"
#include "Render.h"
MovementComponent::MovementComponent()
{
	speed = 1.0f;
}

MovementComponent::MovementComponent(float nowSpeed)
{
	speed = nowSpeed;
}

void MovementComponent::init()
{
	pos = entity->GetComponent<PostitionComponent>();
}

void MovementComponent::update()
{
	int stateLeft = GLFWGetKeyState(GLFW_KEY_LEFT);
	if (stateLeft == GLFW_PRESS)
	{
		pos->SetPos(pos->GetPos() + glm::vec3(-1, 0, 0));
	}

	int stateRight = GLFWGetKeyState(GLFW_KEY_RIGHT);
	if (stateRight == GLFW_PRESS)
	{
		pos->SetPos(pos->GetPos() + glm::vec3(1, 0, 0));
	}

	int stateUp = GLFWGetKeyState(GLFW_KEY_UP);
	if (stateUp == GLFW_PRESS)
	{
		pos->SetPos(pos->GetPos() + glm::vec3(0, 1, 0));
	}

	int stateDown = GLFWGetKeyState(GLFW_KEY_DOWN);
	if (stateDown == GLFW_PRESS)
	{
		pos->SetPos(pos->GetPos() + glm::vec3(0, -1, 0));
	}
}
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
	glm::vec3 resVec;
	int stateDown = GLFWGetKeyState(GLFW_KEY_DOWN);
	int stateLeft = GLFWGetKeyState(GLFW_KEY_LEFT);
	int stateRight = GLFWGetKeyState(GLFW_KEY_RIGHT);
	int stateUp = GLFWGetKeyState(GLFW_KEY_UP);

	if (stateLeft == GLFW_PRESS && stateRight == GLFW_RELEASE)
	{
		changedHor = false;
		lastActiveHor = GLFW_KEY_LEFT;
	}
	if (stateLeft == GLFW_RELEASE && stateRight == GLFW_PRESS)
	{
		changedHor = false;
		lastActiveHor = GLFW_KEY_RIGHT;
	}
	if (stateLeft == GLFW_RELEASE && stateRight == GLFW_RELEASE)
	{
		changedHor = false;
		lastActiveHor = 0;
	}
	if (stateLeft == GLFW_PRESS && stateRight == GLFW_PRESS && !changedHor)
	{
		changedHor = true;
		lastActiveHor = lastActiveHor == GLFW_KEY_LEFT ? GLFW_KEY_RIGHT : GLFW_KEY_LEFT;
	}

	if (stateUp == GLFW_PRESS && stateDown == GLFW_RELEASE)
	{
		changedVer = false;
		lastActiveVer = GLFW_KEY_UP;
	}
	if (stateUp == GLFW_RELEASE && stateDown == GLFW_PRESS)
	{
		changedVer = false;
		lastActiveVer = GLFW_KEY_DOWN;
	}
	if (stateUp == GLFW_RELEASE && stateDown == GLFW_RELEASE)
	{
		changedVer = false;
		lastActiveVer = 0;
	}
	if (stateUp == GLFW_PRESS && stateDown == GLFW_PRESS && !changedVer)
	{
		changedVer = true;
		lastActiveVer = lastActiveVer == GLFW_KEY_UP ? GLFW_KEY_DOWN : GLFW_KEY_UP;
	}

	switch (lastActiveHor)
	{
		case GLFW_KEY_LEFT:
			pos->SetPos(pos->GetPos() + glm::vec3(-1, 0, 0));
			break;
		case GLFW_KEY_RIGHT:
			pos->SetPos(pos->GetPos() + glm::vec3(1, 0, 0));
			break;
		default:
			break;
	}

	switch (lastActiveVer)
	{
		case GLFW_KEY_UP:
			pos->SetPos(pos->GetPos() + glm::vec3(0, 1, 0));
			break;
		case GLFW_KEY_DOWN:
			pos->SetPos(pos->GetPos() + glm::vec3(0, -1, 0));
			break;
		default:
			break;
	}
}
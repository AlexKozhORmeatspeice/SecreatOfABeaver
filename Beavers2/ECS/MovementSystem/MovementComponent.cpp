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
	pos = entity->GetComponent<Transform>();
}

void MovementComponent::update()
{
	if (!canMove)
		return;
	
	glm::vec3 resVec = glm::vec3(0, 0, 0);
	int stateDown = GLFWGetKeyState(GLFW_KEY_S);
	int stateLeft = GLFWGetKeyState(GLFW_KEY_A);
	int stateRight = GLFWGetKeyState(GLFW_KEY_D);
	int stateUp = GLFWGetKeyState(GLFW_KEY_W);

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
			resVec += glm::vec3(-speed, 0, 0);
			break;
		case GLFW_KEY_RIGHT:
			resVec += glm::vec3(speed, 0, 0);
			break;
		default:
			break;
	}

	switch (lastActiveVer)
	{
		case GLFW_KEY_UP:
			resVec += glm::vec3(0, speed, 0);
			break;
		case GLFW_KEY_DOWN:
			resVec += glm::vec3(0, -speed, 0);
			break;
		default:
			break;
	}
	
	isMoving = (resVec != glm::vec3(0.0f, 0.0f, 0.0f));

	pos->SetPos(pos->GetPos() + resVec);
}

MovementComponent::~MovementComponent()
{
	
}

void MovementComponent::StartMove()
{
	canMove = true;
}

void MovementComponent::StopMove()
{
	canMove = false;
}
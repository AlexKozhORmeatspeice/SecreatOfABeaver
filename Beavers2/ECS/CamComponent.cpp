#include "CamComponent.h"
#include "Render.h"

std::shared_ptr<PositionComponent> CamComponent::pos;
glm::mat4 CamComponent::proj;
void CamComponent::init()
{
	scrollK = 1.0f;

	proj = glm::ortho(-GLFWGetWeidth() / 2.0f * scrollK, GLFWGetWeidth() / 2.0f * scrollK, -GLFWGetHeight() / 2.0f * scrollK, GLFWGetHeight() / 2.0f * scrollK, -1.0f, 1.0f);
	pos = entity->GetComponent<PositionComponent>();
}

void CamComponent::update()
{



	proj = glm::ortho(-GLFWGetWeidth() / 2.0f * scrollK, GLFWGetWeidth() / 2.0f * scrollK, -GLFWGetHeight() / 2.0f * scrollK, GLFWGetHeight() / 2.0f * scrollK, -1.0f, 1.0f);
}
CamComponent::~CamComponent()
{
	
}
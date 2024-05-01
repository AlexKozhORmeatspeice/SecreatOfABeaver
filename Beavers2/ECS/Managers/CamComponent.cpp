#include "CamComponent.h"
#include "Render.h"
#include <algorithm>

PositionComponent* CamComponent::pos;
glm::mat4 CamComponent::proj;
void CamComponent::init()
{
	maxScroll = 3.0f;
	minScroll = 0.5f;

	scrollK = 1.0f;

	proj = glm::ortho(-GLFWGetWeidth() / 2.0f / scrollK, GLFWGetWeidth() / 2.0f / scrollK, -GLFWGetHeight() / 2.0f / scrollK, GLFWGetHeight() / 2.0f / scrollK, -1.0f, 1.0f);
	pos = entity->GetComponent<PositionComponent>();
}

void CamComponent::update()
{
	float scrollYAxis = GLFWGetScrool() * 0.25f;

	scrollK = std::max(minScroll, std::min(scrollK + scrollYAxis, maxScroll)); //clamp scollK between maxScroll and minScroll

	proj = glm::ortho(-GLFWGetWeidth() / 2.0f / scrollK, GLFWGetWeidth() / 2.0f / scrollK, -GLFWGetHeight() / 2.0f / scrollK, GLFWGetHeight() / 2.0f / scrollK, -1.0f, 1.0f);
}
CamComponent::~CamComponent()
{
	
}
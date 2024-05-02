#include "CamComponent.h"
#include "Render.h"

Transform* CamComponent::pos;
glm::mat4 CamComponent::proj;
MovementComponent* CamComponent::movComp;

void CamComponent::init()
{
	maxScroll = 3.0f;
	minScroll = 0.5f;

	scrollK = 1.0f;

	proj = glm::ortho(-GLFWGetWeidth() / 2.0f / scrollK, GLFWGetWeidth() / 2.0f / scrollK, -GLFWGetHeight() / 2.0f / scrollK, GLFWGetHeight() / 2.0f / scrollK, -1.0f, 1.0f);
	
	movComp = entity->GetComponent<MovementComponent>();
	pos = entity->GetComponent<Transform>();
}

void CamComponent::update()
{
	float scrollYAxis = GLFWGetScrool() * 0.25f;

	scrollK = std::max(minScroll, std::min(scrollK + scrollYAxis, maxScroll)); //clamp scollK between maxScroll and minScroll

	proj = glm::ortho(-GLFWGetWeidth() / 2.0f / scrollK, GLFWGetWeidth() / 2.0f / scrollK, -GLFWGetHeight() / 2.0f / scrollK, GLFWGetHeight() / 2.0f / scrollK, -1.0f, 1.0f);
}


void CamComponent::SetPos(glm::vec3 newPos)
{
	if(!movComp->isMoving)
		pos->SetPos(newPos);
}
CamComponent::~CamComponent()
{
	
}
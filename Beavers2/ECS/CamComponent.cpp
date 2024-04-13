#include "CamComponent.h"
#include "Render.h"

std::shared_ptr<PostitionComponent> CamComponent::pos;
glm::mat4 CamComponent::proj;
void CamComponent::init()
{
	proj = glm::ortho(-GetWeidth()/2.0f, GetWeidth() / 2.0f, -GetHeight() / 2.0f, GetHeight() / 2.0f, -1.0f, 1.0f);
	pos = entity->GetComponent<PostitionComponent>();
}


CamComponent::~CamComponent()
{
	
}
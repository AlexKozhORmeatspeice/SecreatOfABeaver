#include "CamComponent.h"
#include "Render.h"

std::shared_ptr<PositionComponent> CamComponent::pos;
glm::mat4 CamComponent::proj;
void CamComponent::init()
{
	proj = glm::ortho(-GetWeidth()/2.0f, GetWeidth() / 2.0f, -GetHeight() / 2.0f, GetHeight() / 2.0f, -1.0f, 1.0f);
	pos = entity->GetComponent<PositionComponent>();
}

void CamComponent::update()
{

}
CamComponent::~CamComponent()
{
	
}
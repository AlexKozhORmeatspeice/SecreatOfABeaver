#include "CamComponent.h"

void CamComponent::init()
{
	proj = glm::ortho(0.0f, 540.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	pos = entity->GetComponent<PostitionComponent>();
}

glm::vec3 CamComponent::GetPos()
{
	return pos.get()->GetPos();
}
glm::mat4 CamComponent::GetProj()
{
	return proj;
}

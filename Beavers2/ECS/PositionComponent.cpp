#include "PositionComponent.h"

PostitionComponent::PostitionComponent()
{
	pos = glm::vec3(0, 0, 0);
}
PostitionComponent::PostitionComponent(glm::vec3 newPos)
{
	pos = newPos;
}

glm::vec3 PostitionComponent::GetPos()
{
	return pos;
}

void PostitionComponent::init()
{
	pos = glm::vec3(0, 0, 0);
}

void PostitionComponent::update()
{
	//pos += glm::vec3(1, 1, 0);
}
void PostitionComponent::SetPos(glm::vec3 newPos)
{
	pos = newPos;
}

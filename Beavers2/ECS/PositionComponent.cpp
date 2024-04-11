#include "PositionComponent.h"

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

}

void PostitionComponent::update()
{
	//pos += glm::vec3(1, 1, 0);
}
void PostitionComponent::SetPos(glm::vec3 newPos)
{
	pos = newPos;
}

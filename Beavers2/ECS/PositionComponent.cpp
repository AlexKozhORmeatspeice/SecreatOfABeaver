#include "PositionComponent.h"

PositionComponent::PositionComponent(glm::vec3 newPos)
{
	pos = newPos;
}

glm::vec3 PositionComponent::GetPos()
{
	return pos;
}

void PositionComponent::init()
{

}

void PositionComponent::update()
{
	//pos += glm::vec3(1, 1, 0);
}
void PositionComponent::SetPos(glm::vec3 newPos)
{
	pos = newPos;
}

PositionComponent::~PositionComponent()
{
	
}

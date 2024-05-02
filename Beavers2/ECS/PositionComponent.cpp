#include "PositionComponent.h"

Transform::Transform()
{
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}


Transform::Transform(glm::vec3 newPos, glm::vec3 newScale, glm::vec3 newRot)
{
	pos = newPos;
	scale = newScale;
	rotation = newRot;
}

Transform::Transform(glm::vec3 newPos, glm::vec3 newScale)
{
	pos = newPos;
	scale = newScale;
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}
Transform::Transform(glm::vec3 newPos)
{
	pos = newPos;
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 Transform::GetPos()
{
	return pos;
}
void Transform::SetPos(glm::vec3 newPos)
{
	pos = newPos;
}

glm::vec3 Transform::GetScale()
{
	return scale;
}
void Transform::SetScale(glm::vec3 newScale)
{
	scale = newScale;
}

glm::vec3 Transform::GetRot()
{
	return rotation;
}
void Transform::SetRot(glm::vec3 newRot)
{
	rotation = newRot;
}


void Transform::init()
{

}

void Transform::update()
{
	//pos += glm::vec3(1, 1, 0);
}


Transform::~Transform()
{
	
}

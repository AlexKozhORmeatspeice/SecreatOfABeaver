#pragma once
#include "Components.h"
#include "glm/glm.hpp"

class PostitionComponent : public Component
{
private:
	glm::vec3 pos;

public:
	PostitionComponent()
	{
		pos = glm::vec3(0, 0, 0);
	}
	PostitionComponent(glm::vec3 newPos)
	{
		pos = newPos;
	}

	glm::vec3 GetPos()
	{
		return pos;
	}

	void init() override
	{
		pos = glm::vec3(0, 0, 0);
	}

	void update() override
	{
		//pos += glm::vec3(1, 1, 0);
	}
	void SetPos(glm::vec3 newPos)
	{
		pos = newPos;
	}
};
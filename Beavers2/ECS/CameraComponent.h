#pragma once
#include "Components.h"


class CameraComponent : public Component
{
private:
	glm::vec3 pos;
	glm::mat4 proj;
public:
	void init() override
	{
		proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		pos = entity->GetComponent<PostitionComponent>().GetPos();
	}

	void update() override
	{
		//pos += glm::vec3(1, 1, 0);
	}
	void SetPos(glm::vec3 newPos)
	{
		pos = newPos;
	}
	glm::vec3 GetPos()
	{
		return pos;
	}
	glm::mat4 GetProj()
	{
		return proj;
	}
};
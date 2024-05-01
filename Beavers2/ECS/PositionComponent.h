#pragma once
#include "Render.h"
#include "ECS.h"


class PositionComponent : public Component
{
private:
	glm::vec3 pos;

public:
	PositionComponent();
	PositionComponent(glm::vec3 newPos);

	glm::vec3 GetPos();

	void init() override;

	void update() override;
	void SetPos(glm::vec3 newPos);

	~PositionComponent();
};
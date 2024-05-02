#pragma once
#include "ECS.h"
#include "Render.h"


class UIElement : public Component
{
public:
	float width;
	float height;
	
	glm::vec2 coords;

	UIElement();
	void SetCoords(glm::vec2 newCoords);
};
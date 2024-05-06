#pragma once
#include "ECS.h"
#include "Render.h"


class UIElement : public Component
{
protected:
	bool enabled;

public:
	float width;
	float height;
	
	glm::vec2 coords;

	UIElement();
	void SetCoords(glm::vec2 newCoords);

	void inline Disable()
	{
		enabled = false;
	}
	void inline Enable()
	{
		enabled = true;
	}

	bool inline IsEnabled()
	{
		return enabled;
	}
};
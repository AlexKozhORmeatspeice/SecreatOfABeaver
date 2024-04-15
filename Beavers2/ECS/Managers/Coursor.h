#pragma once
#include "Components.h"

class Coursor : public Component
{
private:
	static Entity* checkBox;
	static std::shared_ptr<PositionComponent> posBox;

	static glm::vec3 mousePos;
public:
	void update() override;
	void init() override;

	static bool GetCollision(Entity* collider);
	static inline glm::vec3 GetMousePos()
	{
		return mousePos;
	}
};
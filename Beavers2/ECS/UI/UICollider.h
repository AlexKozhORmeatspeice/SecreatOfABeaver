#pragma once
#include "ECS.h"
#include "UIElement.h"
#include "Coursor.h"

class UICollider : public Component
{
private:
	bool isCollidWithMouse;
	static bool gotCollisionAny;
public:
	float width;		//set in object on which it's collider
	float height;	   //
	glm::vec2 coords; //

	UICollider();

	void init() override;
	void update() override;
	void lastUpdate() override;

	bool GetIsCollidMouth();
};
#include "UICollider.h"
#include "UIButton.h"

bool UICollider::gotCollisionAny;
UICollider::UICollider()
{

}

void UICollider::init()
{
	width = 1.0f;
	height = 1.0f;
	coords = glm::vec2(0.0f);

	gotCollisionAny = false;
}
void UICollider::update()
{
	if (!entity->GetComponent<UIButton>()->IsEnabled())
		return;

	glm::vec2 mP = Coursor::GetNormalizedMousePos(); //mouse pos
	glm::vec2 tL = coords + glm::vec2(-width, height); //top left
	glm::vec2 bR = coords + glm::vec2(width, -height); //bottom right
	
	isCollidWithMouse = (mP.y <= tL.y && 
						 mP.x >= tL.x && 
						 mP.y >= bR.y &&
						 mP.x <= bR.x   );

	Coursor::isOnUI = isCollidWithMouse;
}

void UICollider::lastUpdate()
{
	gotCollisionAny = false;
}

bool UICollider::GetIsCollidMouth()
{
	return isCollidWithMouse;
}
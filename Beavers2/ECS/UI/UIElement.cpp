#include "UIElement.h"

UIElement::UIElement()
{
	width = 1.0f;
	height = 1.0f;
	coords = glm::vec2(0.0f);
}


void UIElement::SetCoords(glm::vec2 newCoords)
{
	coords = newCoords;
}
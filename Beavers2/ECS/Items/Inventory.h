#pragma once
#include "ECS.h"
#include "Item.h"
#include "SpriteComponent.h"
#include "UIButton.h"
#include "DamageWeapon.h"
#include "Hero.h"

class Inventory : public Component
{
private:
	float maxWeight = 30.0f;
	float nowWeight;
	std::vector<Item*> items;
	std::vector<UIButton*> buttons;
	
	const float spacing      = 0.3f;   //in gl coords
	const float buttonWidth  = 0.2f;   //in gl coords
	const float buttonHeight = 0.2f;   //in gl coords
	
	glm::vec2 itemStartCoords = glm::vec2(-0.8f, -0.8f);
public:
	void init() override;
	void update() override;
	void lastDraw() override;

	void AddItem(Item* item);
	void RemoveItem(Item* item);
};
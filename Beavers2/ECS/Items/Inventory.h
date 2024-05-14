#pragma once
#include "ECS.h"
#include "Item.h"
#include "UI.h"


class Inventory : public Component
{
private:
	static UIIcon* background;
	static UIButton* dropItemButton;
	static int m_inventories;

	UIIcon* heroIcon;
	UIText* heroNameTxt;

	float maxWeight = 30.0f;
	float nowWeight;
	std::vector<Item*> items;
	std::vector<UIButton*> buttons;
	
	const float spacing      = 0.3f;   //in gl coords
	const float buttonWidth  = 0.2f;   //in gl coords
	const float buttonHeight = 0.2f;   //in gl coords
	
	glm::vec2 itemStartCoords;
public:
	void init() override;
	void update() override;
	void lastDraw() override;

	void AddItem(Item* item);
	void RemoveItem(Item* item);

	~Inventory();
};
#pragma once
#include "ECS.h"
#include "Item.h"
#include "UI.h"
#include "DamageWeapon.h"

class Inventory : public Component
{
private:
	UIIcon* background;

	UIButton* dropItemButton;
	UIText*   dropItemText;

	UIButton* takeItemButton;
	UIText*   takeItemText;

	UIIcon* heroIcon;
	UIText* heroNameTxt;

	float maxWeight;
	float nowWeight;
	
	std::vector<Item*> all_items;
	std::vector<UIButton*> buttons;
	
	const float spacing      = 0.2f;   //in gl coords
	const float buttonWidth  = 0.15f;   //in gl coords
	const float buttonHeight = 0.15f;   //in gl coords
	
	glm::vec2 itemStartCoords;
public:
	Inventory();

	void init() override;
	void update() override;
	void lastDraw() override;

	void AddItem(Item* item);
	void RemoveItem(Item* item);

	~Inventory();

private:
	void CreateUI();

	void EnableUI();
	void DisableUI();

	void DrawOtherItemsUnactive(Item* item);
	void TakeFirstNearItem();
};
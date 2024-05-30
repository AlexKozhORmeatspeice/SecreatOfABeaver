#pragma once
#include "ECS.h"
#include "Item.h"
#include "UI.h"
#include "DamageWeapon.h"
#include "SavebleObj.h"
#include "SaveManager.h"
#include "Funcs.h"
		
class Inventory : public Component, SavebleObj
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
	bool isGotKey;
public:
	Inventory();

	void init() override;
	void update() override;
	void lastDraw() override;

	void AddItem(Item* item);
	void RemoveItem(Item* item);

	~Inventory();


	void DrawAllItemsUnactive();
	bool GotKey()
	{
		return isGotKey;
	}
	void DropAllItems()
	{
		while (all_items.size() != 0)
		{
			RemoveItem(all_items[0]);
		}
	}
	void SaveData() override;
	void LoadData() override;
private:
	void CreateUI();

	void EnableUI();
	void DisableUI();

	void DrawOtherItemsUnactive(Item* item);
	void TakeFirstNearItem();
};
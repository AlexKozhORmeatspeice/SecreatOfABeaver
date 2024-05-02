#pragma once
#include "ECS.h"
#include "Item.h"


class Inventory : public Component
{
private:
	int maxItems;
	int nowItems;
	std::vector<Item*> items;
	
public:
	void init() override;
	void update() override;
	void draw() override;

	void AddItem(Item* item);
	void RemoveItem(Item* item);
};
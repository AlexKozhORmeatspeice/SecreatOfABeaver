#include "Inventory.h"

void Inventory::init() 
{

}
void Inventory::update()
{

}
void Inventory::draw()
{

}

void Inventory::AddItem(Item* item)
{
	if (items.size() < nowItems + 1)
	{
		items.push_back(item);
	}
}
void Inventory::RemoveItem(Item* item)
{
	auto it = std::find(items.begin(), items.end(), item);
	if (it != items.end())
		items.erase(it);

	//TODO: drop item as object
}
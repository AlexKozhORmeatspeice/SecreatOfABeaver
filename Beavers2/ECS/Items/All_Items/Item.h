#pragma once
#include "ECS.h"
#include "Hero.h"
enum ItemName
{
	n_Knife, n_Pistol, n_Shotgun, n_Key, None
};
class Item : public Component
{
protected:
	ItemName itemName;
	Hero* onHero;
	float weight;

	float rangeUse;
	unsigned int useCost;
	float timeBetweenUse;
public:
	bool isInInventory;

	virtual void UseItem() {}
	virtual bool CanUse() { return true; }
	Item()
	{
		weight = 0.0f;
		useCost = 0.0f;
		timeBetweenUse = 0.0f;
		rangeUse = 150.0f;

		onHero = nullptr;
		isInInventory = false;

		onHero = nullptr;
		isInInventory = false;
	}

	Item(float nowWeight, float nowRangeUse, unsigned int nowUseCost, float nowTimeBetweenUse)
	{
		weight = nowWeight;

		rangeUse = nowRangeUse;
		useCost = nowUseCost;
		timeBetweenUse = nowTimeBetweenUse;

		onHero = nullptr;
		isInInventory = false;

		itemName = ItemName::None;
	}

	void SetHero(Hero* newHero)
	{
		onHero = newHero;
	}

	float inline GetWeight()
	{
		return weight;
	}

	float GetRange()
	{
		return rangeUse;
	}
	unsigned int GetUseCost()
	{
		return useCost;
	}

	float GetTimeBetween()
	{
		return timeBetweenUse;
	}

	void SetItemName(ItemName name)
	{
		itemName = name;
	}
	~Item() {}
};
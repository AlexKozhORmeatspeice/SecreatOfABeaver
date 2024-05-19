#pragma once
#include "ECS.h"
#include "Hero.h"

class Item : public Component
{
protected:
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
	
	~Item() {}
};
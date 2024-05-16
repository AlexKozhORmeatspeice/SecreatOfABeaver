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
public:
	bool isInInventory;

	virtual void UseItem() {}
	virtual bool CanUse() { return true; }

	Item(float nowWeight)
	{
		weight = nowWeight;

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
	
	~Item() {}
};
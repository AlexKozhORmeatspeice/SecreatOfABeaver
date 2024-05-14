#pragma once
#include "ECS.h"
#include "Hero.h"

class Item : public Component
{
protected:
	Hero* onHero;
	bool isChoosed;
	float weight;
public:
	bool isInInventory;
	Item(float nowWeight)
	{
		weight = nowWeight;

		onHero = nullptr;
		isInInventory = false;
		isChoosed = false;
	}

	void SetHero(Hero* newHero)
	{
		onHero = newHero;
	}

	float inline GetWeight()
	{
		return weight;
	}

	
	~Item() {}
};
#pragma once
#include "ECS.h"
#include "Item.h"

class Weapon : public Item
{
protected:
	unsigned int maxAmmo;
	unsigned int nowAmmo;

	unsigned int damage;
public:
	Weapon(unsigned int nowDamage, unsigned int nowUseCost, float nowWeight, float nowRangeAttack) : Item(nowWeight)
	{
		damage = nowDamage;
		useCost = nowUseCost;
		rangeUse = nowRangeAttack;
	}


	virtual void UseItem() override {}
	virtual bool CanUse() override { return true; }
	~Weapon() {}
};
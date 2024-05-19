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
	Weapon(unsigned int nowDamage, unsigned int nowUseCost, float nowWeight, float nowRangeAttack, float nowTimeBetweenUse)
	{
		weight = nowWeight;
		rangeUse = nowRangeAttack;
		useCost = nowUseCost;
		timeBetweenUse = nowTimeBetweenUse;

		maxAmmo = 0;
		nowAmmo = 0;

		damage = nowDamage;
	}


	virtual void UseItem() override {}
	virtual bool CanUse() override { return true; }
	~Weapon() {}
};
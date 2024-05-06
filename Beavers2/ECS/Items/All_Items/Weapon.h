#pragma once
#include "ECS.h"
#include "Item.h"

class Weapon : public Item
{
protected:
	unsigned int maxAmmo;
	unsigned int nowAmmo;

	float rangeAttack;
	unsigned int damage;
	unsigned int useCost;

	bool isChoosed;
public:
	Weapon(unsigned int nowDamage, unsigned int nowUseCost, float nowWeight, float nowRangeAttack) : Item(nowWeight)
	{
		damage = nowDamage;
		useCost = nowUseCost;
		rangeAttack = nowRangeAttack;
	}

	void update() override;
	virtual void UseWeapon() {}

	void inline ChangeChoosedStatus()
	{
		isChoosed = !isChoosed;
	}


	~Weapon() {}
};
#pragma once
#include "ECS.h"
#include "Weapon.h"
#include "Enemy.h"

class DamageWeapon : public Weapon
{
public:
	DamageWeapon(unsigned int nowDamage, unsigned int nowUseCost, float nowWeight, float nowRangeAttack, float nowTimeBetweenUse)
		: Weapon(nowDamage, nowUseCost, nowWeight, nowRangeAttack, nowTimeBetweenUse)
	{}

	void UseItem() override;
	bool CanUse() override;
	~DamageWeapon() {}
};
#pragma once
#include "Item.h"

class Weapon : public Item
{
private:
	unsigned int maxAmmo;
	unsigned int nowAmmo;

	float rangeAttack;
	unsigned int damage;
	unsigned int useCost;
public:

	Weapon(unsigned int nowDamage, unsigned int nowUseCost);


};
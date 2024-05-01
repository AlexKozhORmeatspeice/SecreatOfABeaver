#pragma once
#include "ECS.h"

class HP : public Component
{
private:
	unsigned int maxHP = 100;
	unsigned int nowHP;
public:
	HP();
	HP(unsigned int nowMaxHP);

	void init() override;
	
	void UseHP(unsigned int useHP);
	void Recover();
	bool isDead();
};
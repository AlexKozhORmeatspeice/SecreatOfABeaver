#pragma once
#include "HP.h"
#include "Stamina.h"

class Enemy : public Component
{
private:
	Stamina* stamina;
	HP* hp;


public:
	bool isChoosed;
	bool inFight;
	bool canTakeAction;

	void init() override;
	void update() override;
};
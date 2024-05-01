#pragma once
#include "ECS.h"

#include "HP.h"
#include "Stamina.h"

#include "Collider.h"

#include "Render.h"
#include "Coursor.h"

class Hero : public Component
{
private:
	static std::vector<Hero*> heroes;
	Stamina* stamina;
	HP* hp;

public:
	bool isChoosed;

	bool canTakeAction;
	bool inFight;

	void init() override;
	void update() override;

	~Hero();
private:
	void CheckIsChoosed();
	void SetOtherNotChoosed(Hero* exceptHero);
};
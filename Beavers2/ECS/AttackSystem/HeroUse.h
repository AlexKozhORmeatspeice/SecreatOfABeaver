#pragma once
#include "ECS.h"
#include "Weapon.h"
#include "TimeManager.h"

class HeroUse : public Component
{
private:
	Item* item;

	float lastTimeUse;
public:
	HeroUse()
	{
		item = nullptr;
		lastTimeUse = Time::GetCurrentTime();
	}

	void update() override;

	void SetItem(Item* item);
	void NoItem();

	Item* GetNowItem();
};
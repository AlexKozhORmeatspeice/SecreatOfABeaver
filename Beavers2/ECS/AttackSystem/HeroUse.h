#pragma once
#include "ECS.h"
#include "Weapon.h"

class HeroUse : public Component
{
private:
	Item* item;
public:
	void update() override;

	void SetItem(Item* item);
	void NoItem();

	Item* GetNowItem();
};
#pragma once
#include "ECS.h"
#include "Item.h"
#include "DamageWeapon.h"

class ItemCreator
{
private:
	static float standartSizeIcon;
public:
	static DamageWeapon& CreateKnife(glm::vec3 pos);
};
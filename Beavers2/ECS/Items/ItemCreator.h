#pragma once
#include "ECS.h"
#include "Item.h"
#include "DamageWeapon.h"

class ItemCreator
{
private:
	static float standartSizeIcon;

	static float meleeAttackRange;
	static float middleAttackRange;
	static float longAttackRange;
public:
	static DamageWeapon& CreateKnife(glm::vec3 pos);
	static DamageWeapon& CreateShotgun(glm::vec3 pos);
	static DamageWeapon& CreatePistol(glm::vec3 pos);
};
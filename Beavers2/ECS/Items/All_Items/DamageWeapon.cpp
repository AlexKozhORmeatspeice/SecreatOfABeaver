#include "DamageWeapon.h"



void DamageWeapon::UseItem()
{
	Enemy* enemy = Coursor::GetCollision<Enemy>();
	if (!enemy)
		return;
	enemy->entity->GetComponent<HP>()->GetDamage(damage);
}

bool DamageWeapon::CanUse()
{
	Enemy* enemy = Coursor::GetCollision<Enemy>();

	return (enemy != nullptr);
}
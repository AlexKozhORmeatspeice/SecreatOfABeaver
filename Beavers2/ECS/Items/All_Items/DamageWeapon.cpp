#include "DamageWeapon.h"



void DamageWeapon::UseWeapon()
{
	Enemy* enemy = Coursor::GetCollision<Enemy>();
	if (!enemy)
		return;

	enemy->entity->GetComponent<HP>()->GetDamage(damage);
	isChoosed = false;
}

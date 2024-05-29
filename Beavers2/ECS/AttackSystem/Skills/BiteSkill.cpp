#include "BiteSkill.h"

float BiteSkill::damage = 50.0f;


void BiteSkill::Attack()
{
	Enemy* enemy = Coursor::GetCollision<Enemy>();
	if (!enemy)
		return;
	enemy->entity->GetComponent<HP>()->GetDamage(damage);
}

#include "Enemy.h"

void Enemy::init()
{
	inFight = false;
	isChoosed = false;
	canTakeAction = false;

	hp = entity->GetComponent<HP>();
	stamina = entity->GetComponent<Stamina>();
}

void Enemy::update()
{
	if (hp->isDead())
	{
		isChoosed = false;
		canTakeAction = false;
		inFight = false;

		entity->destroy();
	}

	if (!inFight)
	{
		canTakeAction = false;

		stamina->Recover();
	}
}
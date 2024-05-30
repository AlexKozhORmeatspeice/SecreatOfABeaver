#pragma once
#include "ECS.h"
#include "Weapon.h"
#include "Enemy.h"
#include "TimeManager.h"

class EnemyAttack : public Component
{
private:
	Enemy* enemy;
	Transform* trans;
	Hero* nowTarget;

	Stamina* stamina;
	bool canAttack;

	float v_damage;
	float v_rangeAttack;
	int v_attackCost;

	bool enoughStamina;

	float lastTimeAttack;
	float timeBetweenAttacks;
public:
	EnemyAttack()
	{
		timeBetweenAttacks = 1.0f;

		v_rangeAttack = 200.0f;
		v_damage = 40.0f;
		v_attackCost = 50;
	}

	EnemyAttack(float _damage, float _range, float _cost)
	{
		timeBetweenAttacks = 1.0f;

		v_rangeAttack = _range;
		v_damage = _damage;
		v_attackCost = _cost;
	}


	void init() override
	{
		timeBetweenAttacks = 1.0f;
		lastTimeAttack = Time::GetCurrentTime();

		enoughStamina = true;
		nowTarget = nullptr;

		stamina = entity->GetComponent<Stamina>();

		trans = entity->GetComponent<Transform>();
		enemy = entity->GetComponent<Enemy>();
	}

	void update() override
	{
		if (!enemy->canTakeAction)
			return;

		enoughStamina = (stamina->GetNowStamina() >= v_attackCost);
		if (!enemy->IsSeeHero() || !enoughStamina)
		{
			canAttack = false;
			return;
		}
		float dist = glm::distance(trans->GetPos(), enemy->GetLastHeroPos());
		nowTarget = enemy->GetTargetHero();
		canAttack = dist <= v_rangeAttack && nowTarget != nullptr;

		if (canAttack && enoughStamina && Time::GetCurrentTime() - lastTimeAttack >= timeBetweenAttacks)
			Attack();
	}

	bool inline IsCanAttack()
	{
		return canAttack;
	}
private:
	void Attack()
	{
		if (enoughStamina && nowTarget != nullptr)
		{
			lastTimeAttack = Time::GetCurrentTime();
			stamina->UseStamina(v_attackCost);
			HP* heroHP = nowTarget->entity->GetComponent<HP>();
			heroHP->GetDamage(v_damage);
		}
	}
};
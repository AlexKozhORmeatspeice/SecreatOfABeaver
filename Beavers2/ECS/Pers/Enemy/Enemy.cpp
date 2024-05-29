#include "Enemy.h"
#include "StepSystemManager.h"

float Enemy::minStamina = 10.0f;

Enemy::Enemy()
{
	viewDist = 400.0f;
}

Enemy::Enemy(float _viewDist)
{
	viewDist = _viewDist;
}

void Enemy::init()
{
	seeHero = false;

	checkCircle = &Manager::addEntity();

	checkCircle->AddComponent<Transform>();
	checkCirclePos = checkCircle->GetComponent<Transform>();

	checkCircle->AddComponent<CircleCollider>(viewDist, false, false);

	pos = entity->GetComponent<Transform>();

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
		StepSysManager::RefreshList();
		return;
	}

	if (stamina->GetNowStamina() < minStamina)
	{
		canTakeAction = false;
	}

	CheckHero();
	//if see hero start fight
	if (seeHero && heroPos != nullptr && !StepSysManager::instance->IsInFight())
	{
		StepSysManager::instance->StartFight();
	}

	
}

Enemy::~Enemy()
{
	entity = nullptr;
	checkCircle->destroy();
}

void Enemy::CheckHero()
{
	checkCirclePos->SetPos(pos->GetPos());

	std::vector< Collider*> heroObjs_coll = checkCircle->GetComponent<CircleCollider>()->GetCollidObjs<Hero>();

	if (heroObjs_coll.size() != 0)
	{
		//find the nearest hero
		float mDist = 1 << 30;
		for (auto& hero_coll : heroObjs_coll)
		{
			Transform* nowHero_trans = hero_coll->entity->GetComponent<Transform>();
			if (nowHero_trans != nullptr && glm::distance(pos->GetPos(), nowHero_trans->GetPos()) <= mDist)
			{
				mDist = glm::distance(pos->GetPos(), nowHero_trans->GetPos());
				heroPos = nowHero_trans;
			}
		}
	}


	seeHero = (heroPos != nullptr &&
		Raycast::CheckCollision<Hero>(pos->GetPos(), heroPos->GetPos() - pos->GetPos(), entity)
		);

	if (seeHero && heroPos != nullptr)
	{
		lastHeroPos = heroPos->GetPos();
	}
	else
	{
		heroPos = nullptr;
	}
}

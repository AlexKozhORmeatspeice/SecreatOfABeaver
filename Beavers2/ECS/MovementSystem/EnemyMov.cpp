#include "EnemyMov.h"

EnemyMovement::EnemyMovement()
{
	viewDir = glm::vec3(1, 0, 0);
	viewDist = 10.0f;
	speed = 1.0f;
}

EnemyMovement::EnemyMovement(float nowViewDist, float nowSpeed)
{
	viewDir = glm::vec3(1, 0, 0);
	viewDist = nowViewDist;
	speed = nowSpeed;
}

void EnemyMovement::init()
{
	pos = entity->GetComponent<PositionComponent>();

	checkCircle = &CreatObj();

	checkCircle->AddComponent<PositionComponent>();
	checkCirclePos = checkCircle->GetComponent<PositionComponent>();

	checkCircle->AddComponent<CircleCollider>(viewDist, false, false);
}

void EnemyMovement::update()
{
	checkCirclePos->SetPos(pos->GetPos());

	Collider* collidObj = checkCircle->GetComponent<CircleCollider>()->GetColllidObj();
	Entity* entityHero = nullptr;

	bool isHeroCollid = false;
	if (collidObj != nullptr)
	{
		entityHero = collidObj->entity;
		isHeroCollid = entityHero->HasComponent<Hero>();
	}
		

	if (isHeroCollid)
	{
		if(heroPos == nullptr)
			heroPos = entityHero->GetComponent<PositionComponent>();

		Move();
	}
	else
	{
		heroPos = nullptr;
	}
}

void EnemyMovement::Move()
{
	viewDir = heroPos->GetPos() - pos->GetPos();
	viewDir /= glm::length(viewDir);

	pos->SetPos(pos->GetPos() + viewDir * speed);
}
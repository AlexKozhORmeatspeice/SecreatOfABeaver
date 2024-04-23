#include "EnemyMov.h"

EnemyMov::EnemyMov()
{
	viewDir = glm::vec3(1, 0, 0);

	speed = stamina->GetCellSize();
}

EnemyMov::EnemyMov(float nowViewDist, unsigned int nowMoveCost)
{
	viewDir = glm::vec3(1, 0, 0);

	viewDist = nowViewDist;
	moveCost = nowMoveCost;

	speed = stamina->GetCellSize();
}

void EnemyMov::init()
{
	pos = entity->GetComponent<PositionComponent>();

	checkCircle = &CreatObj();

	checkCircle->AddComponent<PositionComponent>();
	checkCirclePos = checkCircle->GetComponent<PositionComponent>();

	checkCircle->AddComponent<CircleCollider>(viewDist, false, false);
}

void EnemyMov::update()
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
		
	//TODO: change to stamina system movement
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

void EnemyMov::Move()
{
	viewDir = heroPos->GetPos() - pos->GetPos();
	viewDir /= glm::length(viewDir);

	pos->SetPos(pos->GetPos() + viewDir * speed);
}

EnemyMov::~EnemyMov()
{
	delete checkCircle;
}

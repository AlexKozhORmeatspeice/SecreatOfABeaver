#include "EnemyMov.h"

EnemyMov::EnemyMov()
{
	viewDir = glm::vec3(1, 0, 0);

	speed = stamina->GetCellSize() / 5.0f;
}

EnemyMov::EnemyMov(float nowViewDist, unsigned int nowMoveCost)
{
	viewDir = glm::vec3(1, 0, 0);

	viewDist = nowViewDist;
	moveCost = nowMoveCost;

	speed = stamina->GetCellSize() / 5.0f;
}

void EnemyMov::init()
{
	enemy = entity->GetComponent<Enemy>();
	pos = entity->GetComponent<PositionComponent>();

	checkCircle = &Manager::addEntity();

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
	if (collidObj != nullptr && collidObj != entity->GetComponent<BoxCollider>())
	{
		StepSysManager::instance->StartFight();
		entityHero = collidObj->entity;
		isHeroCollid = entityHero->HasComponent<Hero>();
	}
	
	
	//TODO: change to stamina system movement
	if (isHeroCollid && (entityHero != nullptr && heroPos == nullptr))
	{
		StepSysManager::instance->StartFight();
		heroPos = entityHero->GetComponent<PositionComponent>();
	}
	else
	{
		entityHero = nullptr;
		heroPos = nullptr;
	}

	if (enemy->canTakeAction)
		Move();
}

void EnemyMov::Move()
{
	viewDir = heroPos->GetPos() - pos->GetPos();
	viewDir /= glm::length(viewDir);

	pos->SetPos(pos->GetPos() + viewDir * speed);
}

EnemyMov::~EnemyMov()
{

}

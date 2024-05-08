#include "EnemyMov.h"

EnemyMov::EnemyMov()
{
	viewDir = glm::vec3(1, 0, 0);

	speed = stamina->GetCellSize() / 10.0f;
}

EnemyMov::EnemyMov(float nowViewDist, unsigned int nowMoveCost)
{
	viewDir = glm::vec3(1, 0, 0);

	viewDist = nowViewDist;
	moveCost = nowMoveCost;

	speed = stamina->GetCellSize() / 10.0f;
}

void EnemyMov::init()
{
	seeHero = false;

	enemy = entity->GetComponent<Enemy>();
	pos = entity->GetComponent<Transform>();

	checkCircle = &Manager::addEntity();

	checkCircle->AddComponent<Transform>();
	checkCirclePos = checkCircle->GetComponent<Transform>();

	checkCircle->AddComponent<CircleCollider>(viewDist, false, false);
}

void EnemyMov::update()
{
	checkCirclePos->SetPos(pos->GetPos());

	Collider* collidObj = checkCircle->GetComponent<CircleCollider>()->GetCollidObj<Hero>();
	
	//TODO: change to stamina system movement
	if (collidObj != nullptr && heroPos == nullptr)
	{
		heroPos = collidObj->entity->GetComponent<Transform>();
	}
	

	seeHero = (heroPos != nullptr &&
			   Raycast::CheckCollision<Hero>(pos->GetPos(), heroPos->GetPos() - pos->GetPos(), entity)
			  );

	if (!seeHero)
	{
		heroPos = nullptr;
	}
	
	std::cout << seeHero << std::endl;

	//if see hero start fight
	/*if (seeHero && heroPos != nullptr && !StepSysManager::instance->IsInFight())
	{
		StepSysManager::instance->StartFight();
	}*/

	if (enemy->canTakeAction)
		Move();
}

void EnemyMov::Move()
{
	bool GetCollisionWithHero = entity->GetComponent<BoxCollider>()->IsColllidWith<BoxCollider>(heroPos->entity);
	if (GetCollisionWithHero)
	{
		enemy->canTakeAction = false;
		heroPos = nullptr;
		return;
	}

	CamComponent::SetPos(pos->GetPos());

	viewDir = heroPos->GetPos() - pos->GetPos();
	viewDir /= glm::length(viewDir);


	if (seeHero)
	{
		pos->SetPos(pos->GetPos() + viewDir * speed);
	}
	{
		enemy->canTakeAction = false;
	}
}

EnemyMov::~EnemyMov()
{
	checkCircle->destroy();
}

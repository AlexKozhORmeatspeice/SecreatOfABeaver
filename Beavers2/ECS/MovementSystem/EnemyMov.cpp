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
		StepSysManager::instance->StartFight();
		heroPos = collidObj->entity->GetComponent<Transform>();
	}

	if (enemy->canTakeAction)
		Move();
}

void EnemyMov::Move()
{
	bool GetCollisionWithHero = entity->GetComponent<BoxCollider>()->IsColllidWith<BoxCollider>(heroPos->entity);

	if (GetCollisionWithHero)
	{
		std::cout << 1 << std::endl;
		enemy->canTakeAction = false;
		heroPos = nullptr;
		return;
	}

	CamComponent::SetPos(pos->GetPos());

	viewDir = heroPos->GetPos() - pos->GetPos();
	viewDir /= glm::length(viewDir);

	pos->SetPos(pos->GetPos() + viewDir * speed);
}

EnemyMov::~EnemyMov()
{
	checkCircle->destroy();
}

#include "EnemyMov.h"

EnemyMov::EnemyMov()
{
	viewDir = glm::vec3(1, 0, 0);
	speed = stamina->GetCellSize() / 10.0f;
}

EnemyMov::EnemyMov( unsigned int nowMoveCost)
{
	viewDir = glm::vec3(1, 0, 0);
	
	moveCost = nowMoveCost;

	speed = stamina->GetCellSize() / 10.0f;
}

void EnemyMov::init()
{
	attackSys = entity->GetComponent<EnemyAttack>();
	enemy = entity->GetComponent<Enemy>();

	wayWalked = 0.0f;
	enemy = entity->GetComponent<Enemy>();
	
	pos = entity->GetComponent<Transform>();

	stamina = entity->GetComponent<Stamina>();

	collider = entity->GetComponent<BoxCollider>();
}

void EnemyMov::update()
{
	if (enemy->canTakeAction && !attackSys->IsCanAttack())
		Move();
}

void EnemyMov::Move()
{
	Collider* heroColl = collider->GetCollidObj<Hero>();

	float v_useStamina = wayWalked / stamina->GetCellSize() * moveCost;
	if (v_useStamina > 1.0f && v_useStamina <= stamina->GetNowStamina())
	{
		stamina->UseStamina(v_useStamina);
		wayWalked = 0.0f;
	}
	if (heroColl ||
		glm::distance(enemy->GetLastHeroPos(), pos->GetPos()) <= 10.0f || 
		v_useStamina > stamina->GetNowStamina() ||
		attackSys->IsCanAttack())
	{
		wayWalked = 0.0f;

		wayWalked = 0.0f;
		
		return;
	}
	
	CamComponent::SetPos(pos->GetPos());
	
	viewDir = enemy->GetLastHeroPos() - pos->GetPos();
	viewDir /= glm::length(viewDir);

	wayWalked += speed;
	pos->SetPos(pos->GetPos() + viewDir * speed);		
}

EnemyMov::~EnemyMov()
{
}
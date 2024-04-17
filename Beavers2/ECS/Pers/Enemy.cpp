#include "Enemy.h"

Enemy::Enemy()
{
	viewDir = glm::vec3(1, 0, 0);
	viewDist = 10.0f;
	viewAngle = 30.0f;
	speed = 1.0f;
}

Enemy::Enemy(float nowViewDist, float nowViewAngle, float nowSpeed)
{
	viewDir = glm::vec3(1, 0, 0);
	viewDist = nowViewDist;
	viewAngle = nowViewAngle;
	speed = nowSpeed;
}

void Enemy::init()
{
	collider = entity->GetComponent<BoxCollider>();
}

void Enemy::update()
{
	float dist = glm::distance(heroPos->GetPos(), pos->GetPos());
	float cosProj = glm::dot(viewDir, heroPos->GetPos()) / (glm::length(viewDir) * glm::length(heroPos->GetPos()));
	float angle = acos(cosProj);

	if (dist <= viewDist && angle <= viewAngle)
	{
		Move();
	}
}

void Enemy::Move()
{
	viewDir = heroPos->GetPos() - pos->GetPos();
	viewDir /= glm::length(viewDir);

}
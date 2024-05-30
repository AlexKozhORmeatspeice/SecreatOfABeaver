#pragma once
#include "HP.h"
#include "Stamina.h"
#include "Hero.h"

class Enemy : public Component
{
private:
	Transform* pos;

	Stamina* stamina;
	HP* hp;

	Transform* heroPos;
	glm::vec3 lastHeroPos;
	
	Entity* checkCircle;
	Transform* checkCirclePos;
	
	bool seeHero;
	float viewDist;

	static float minStamina;
public:
	bool isChoosed;
	bool inFight;
	bool canTakeAction;

	Enemy();
	Enemy(float _viewDist);

	void init() override;
	void update() override;

	
	glm::vec3 inline GetLastHeroPos()
	{
		return lastHeroPos;
	}

	Hero* GetTargetHero()
	{
		if (heroPos != nullptr)
		{
			return heroPos->entity->GetComponent<Hero>();
		}
		else
		{
			return nullptr;
		}
	}
	void SetNoTarget()
	{
		heroPos = nullptr;
	}

	bool inline IsSeeHero()
	{
		return seeHero;
	}

	~Enemy();
private:
	void CheckHero();
};
#pragma once
#include "vector"
#include "ECS.h"

#include "HeroMov.h"
#include "Hero.h"
#include "Enemy.h"


class StepSysManager : public Component
{
private:
	std::vector<Hero*> heroes;
	std::vector<Enemy*> enemies;

	bool inFight;
public:
	static StepSysManager* instance;

	void init() override;
	void update() override;

	void AddHero(Hero* newHero);
	void AddEnemy(Enemy* newEnemy);

	void StartFight();
	void EndFight();

private:
	void SetHeroesFreeToAct();
	void SetEnemiesUnableToAct();

	void RefreshList();
};
#pragma once
#include "vector"
#include "ECS.h"

#include "HeroMov.h"
#include "Hero.h"
#include "Enemy.h"

#include "Render.h"
class StepSysManager : public Component
{
private:
	static std::vector<Hero*> heroes;
	static std::vector<Enemy*> enemies;

	bool inFight;
	bool heroAct;
	static int enemiesActCount;
public:
	static StepSysManager* instance;

	void init() override;
	void update() override;

	void AddHero(Hero& newHero);
	void AddEnemy(Enemy& newEnemy);

	void StartFight();
	void EndFight();

	bool inline IsInFight()
	{
		return inFight;
	}

	static void RefreshList();
private:
	void StartFightLogic();

	void SetHeroesFreeToAct();
	void SetEnemiesUnableToAct();
};
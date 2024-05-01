#include "StepSystemManager.h"

StepSysManager* StepSysManager::instance;

void StepSysManager::init()
{
	inFight = false;

	if (instance == nullptr)
	{
		instance = this;
	}
}
void StepSysManager::update()
{
	RefreshList();
	
	if (!inFight)
		return;
}

void StepSysManager::AddHero(Hero* newHero)
{
	heroes.push_back(newHero);
}
void StepSysManager::AddEnemy(Enemy* newEnemy)
{
	enemies.push_back(newEnemy);
}

void StepSysManager::StartFight()
{
	inFight = true;

	for (Hero* hero : heroes)
	{
		hero->inFight = true;
		hero->canTakeAction = true;
	}

	for (Enemy* enemy : enemies)
	{
		enemy->inFight = true;
		enemy->canTakeAction = false;
	}
}
void StepSysManager::EndFight()
{
	SetHeroesFreeToAct();
	SetEnemiesUnableToAct();

	inFight = false;
}

void StepSysManager::RefreshList()
{
	//remove deleted heroes
	heroes.erase(std::remove_if
	(heroes.begin(), heroes.end(),
	[](Hero* hero) {return hero == nullptr; }
	), heroes.end()
	);

	//remove deleted enemies
	enemies.erase(std::remove_if
	(enemies.begin(), enemies.end(),
		[](Enemy* enemy) {return enemy == nullptr; }
	), enemies.end()
	);
}

void StepSysManager::SetHeroesFreeToAct()
{
	for (Hero* hero : heroes)
	{
		hero->inFight = false;
	}
}
void StepSysManager::SetEnemiesUnableToAct()
{
	for (Enemy* enemy : enemies)
	{
		enemy->inFight = false;
	}
}
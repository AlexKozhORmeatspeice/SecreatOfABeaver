#include "StepSystemManager.h"

StepSysManager* StepSysManager::instance;
int StepSysManager::enemiesActCount;
std::vector<Hero*> StepSysManager::heroes;
std::vector<Enemy*> StepSysManager::enemies;

void StepSysManager::init()
{
	enemiesActCount = 0;
	inFight = false;
	heroAct = true;

	if (instance == nullptr)
	{
		instance = this;
	}

	Entity* textE = &Manager::addEntity();
	text = textE->AddComponent<UIText>("in fight", glm::vec2(-0.2f, 0.7f), 0.05f);
	text->ChangeColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.6f));
}
void StepSysManager::update()
{
	if (!inFight)
	{
		text->Disable();
		return;
	}
	else
	{
		text->Enable();
	}
	
	StartFightLogic();
}

void StepSysManager::StartFightLogic()
{
	if (heroes.size() == 0)
		SceneManager::ReloadScene();

	if (enemies.size() == 0)
		EndFight();

	if (heroAct) //hero logic
	{
		int letterEState = GLFWGetKeyState(GLFW_KEY_E); //if got letter E on keybord stop hero turn

		if (letterEState == GLFW_PRESS)
		{
			std::cout << 2 << std::endl;
			for (auto& hero : heroes)
			{
				hero->entity->GetComponent<Stamina>()->Recover();
				hero->canTakeAction = false;
				heroAct = false;
			}

			for (auto& enemy : enemies)
			{
				Stamina* stam = enemy->entity->GetComponent<Stamina>();
				stam->Recover();
			}
			RefreshList();
			enemies[0]->canTakeAction = true;
		}
	}
	else //enemy logic
	{
		if (enemiesActCount == enemies.size())
		{
			enemiesActCount = 0;
			for (Hero* hero : heroes)
			{
				hero->canTakeAction = true;
			}
			heroAct = true;
			return;
		}
		
		Enemy* enemy = enemies[0];
		if (!enemy->canTakeAction)
		{
			enemies.erase(enemies.begin());
			enemies.push_back(enemy);

			
			enemiesActCount++;
		}
	}
}

void StepSysManager::AddHero(Hero& newHero)
{
	heroes.push_back(&newHero);
}
void StepSysManager::AddEnemy(Enemy& newEnemy)
{
	enemies.push_back(&newEnemy);
}

void StepSysManager::StartFight()
{
	inFight = true;
	heroAct = true;

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
	heroAct = true;
}

void StepSysManager::RefreshList()
{
	//remove deleted heroes
	heroes.erase(std::remove_if
	(heroes.begin(), heroes.end(),
	[](Hero* hero) {return (!hero->entity->isActive()); }
	), heroes.end()
	);

	//remove deleted enemies
	enemies.erase(std::remove_if
	(enemies.begin(), enemies.end(),
		[](Enemy* enemy) {return (!enemy->entity->isActive()); }
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

StepSysManager::~StepSysManager()
{
	instance = nullptr;
	text->entity->destroy();
	enemies.clear();
	heroes.clear();
}
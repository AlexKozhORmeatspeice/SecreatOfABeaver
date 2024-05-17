#include "SceneManager.h"
std::vector<Entity*>& CreateScene1();
std::vector<Entity*>& CreateScene2();

int SceneManager::nowScene;
std::vector<Entity*> SceneManager::currentEntities;
std::vector<std::vector<Entity*>& (*)()> SceneManager::scenesFuncs;

void SceneManager::init()
{
	nowScene = 0;

	scenesFuncs.push_back(CreateScene1);
	scenesFuncs.push_back(CreateScene2);
}

void SceneManager::LoadScene(int n)
{
	nowScene = n;

	ClearScene();
	currentEntities = scenesFuncs[nowScene](); //spawn scenes and give entities
}


void SceneManager::LoadNextScene()
{
	nowScene++;
	LoadScene(nowScene);
}


void SceneManager::ReloadScene()
{
	ClearScene();
	LoadScene(nowScene);
}

void SceneManager::ClearScene()
{
	for (auto entity : currentEntities)
	{
		entity->destroy();
	}
	currentEntities.clear();
}

////////////////////////////////////////////////////////////////////////////////////scenes////////////////////////////////////////////////////////////////////////////////////
std::vector<Entity*>& CreateScene1()
{
	CamComponent::SetPos(glm::vec3(0.0f));
	Entity* floor(&Manager::addEntity());
	Entity* stepSys(&Manager::addEntity());
	

	StepSysManager* stepSM = stepSys->AddComponent<StepSysManager>();

	/////////////////////Heroes and enemies/////////////////////
	Entity* zubar = HeroCreator::ZubarPrefab(glm::vec3(200.0f, 0.0f, 0.0f));
	stepSM->AddHero(*zubar->GetComponent<Hero>()); //!!!

	Entity* zubar2 = HeroCreator::ZubarPrefab(glm::vec3(200.0f, 200.0f, 0.0f));
	stepSM->AddHero(*zubar2->GetComponent<Hero>()); //!!!
	
	Entity* enemy1 = EnemyCreator::BasicEnemyPrefab(glm::vec3(-200.0f, 0.0f, 0.0f));
	stepSM->AddEnemy(*enemy1->GetComponent<Enemy>()); //!!!
	//////////////////////////////////////////////////////////////


	/////////////////////Environment/////////////////////
	floor->AddComponent<Transform>(glm::vec3(0.0f));
	floor->AddComponent<Tile>(1200.0f, 1200.0f, "res/Shaders/Basic.shader", "res/Textures/FloorTexture.png");


	///////////////////////////////////////////////////////////////////
	std::vector<Entity*> entities;
	entities.push_back(floor);
	entities.push_back(stepSys);
	entities.push_back(zubar);
	entities.push_back(enemy1);

	return entities;
}

std::vector<Entity*>& CreateScene2()
{
	std::vector<Entity*> entities;

	return entities;
}
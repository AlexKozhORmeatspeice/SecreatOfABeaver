#include "SceneManager.h"
void CreateScene1(std::vector<Entity*>&);
void CreateScene2(std::vector<Entity*>&);

int SceneManager::nowScene;
std::vector<Entity*> SceneManager::currentEntities;
std::vector<void (*)(std::vector<Entity*>&)> SceneManager::scenesFuncs;

void SceneManager::init()
{
	nowScene = 0;

	scenesFuncs.push_back(CreateScene1);
	scenesFuncs.push_back(CreateScene2);
	scenesFuncs.push_back(CreateScene3);
}

void SceneManager::LoadScene(int n)
{
	nowScene = n;

	ClearScene();
	scenesFuncs[nowScene](currentEntities); //spawn scenes and give entities
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
void CreateScene1(std::vector<Entity*>& vec)
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
	vec.push_back(floor);
	vec.push_back(stepSys);
	vec.push_back(zubar);
	vec.push_back(enemy1);
}

void CreateScene2(std::vector<Entity*>& vec)
{
	CamComponent::SetPos(glm::vec3(0.0f));
	Entity* floor_main(&Manager::addEntity());
	Entity* hallway(&Manager::addEntity());
	Entity* stepSys(&Manager::addEntity());
	Entity* message(&Manager::addEntity());
	StepSysManager* stepSM = stepSys->AddComponent<StepSysManager>();

	floor_main->AddComponent<Transform>(glm::vec3(0.0f, 200.0f, 0.0f));
	floor_main->AddComponent<Tile>(400.0f, 400.0f, "res/Shaders/Basic.shader", "res/Textures/FloorTexture.png");

	hallway->AddComponent<Transform>(glm::vec3(50.0f, 0.0f, 0.0f));
	hallway->AddComponent<Tile>(160.f, 200.0f, 0.0f);
	message->AddComponent<UIText>("Destroy the beaver", glm::vec2(0.0f, 0.8f), 14.0f);

	/////////////////////Heroes and enemies/////////////////////
	Entity* zubar = HeroCreator::ZubarPrefab(glm::vec3(55.0f, 0.0f, 0.0f));
	stepSM->AddHero(*zubar->GetComponent<Hero>()); //!!!

	Entity* zubar2 = HeroCreator::ZubarPrefab(glm::vec3(55.0f, 100.0f, 0.0f));
	stepSM->AddHero(*zubar2->GetComponent<Hero>()); //!!!

	Entity* enemy1 = EnemyCreator::BasicEnemyPrefab(glm::vec3(-200.0f, 150.0f, 0.0f));
	stepSM->AddEnemy(*enemy1->GetComponent<Enemy>()); //!!!
	//////////////////////////////////////////////////////////////
	vec.push_back(floor_main);
	vec.push_back(hallway);
	vec.push_back(stepSys);
	vec.push_back(zubar);
	vec.push_back(zubar2);
	vec.push_back(enemy1);

}
void CreateScene3(std::vector<Entity*>& vec)
{
	CamComponent::SetPos(glm::vec3(0.0f));
	Entity* floor_main1(&Manager::addEntity());
	Entity* floor_main2(&Manager::addEntity());
	Entity* hallway1(&Manager::addEntity());
	Entity* hallway2(&Manager::addEntity());
	Entity* stepSys(&Manager::addEntity());
	StepSysManager* stepSM = stepSys->AddComponent<StepSysManager>();

	floor_main1->AddComponent<Transform>(glm::vec3(0.0f, 300.0f, 0.0f));
	floor_main1->AddComponent<Tile>(300.0f, 200.0f, "res/Shaders/Basic.shader", "res/Textures/FloorTexture.png");
	floor_main2->AddComponent<Transform>(glm::vec3(1500.0f, 0.0f, 0.0f));
	floor_main2->AddComponent<Tile>(360.0f, 240.0f, "res/Shaders/Basic.shader", "res/Textures/FloorTexture.png");

	hallway1->AddComponent<Transform>(glm::vec3(0.0f, -160.0f, 0.0f));
	hallway1->AddComponent<Tile>(40.0f, 120.0f, "res/Shaders/Basic.shader", "res/Textures/FloorTexture.png");
	hallway2->AddComponent<Transform>(glm::vec3(360.0f, 0.0f, 0.0f));
	hallway2->AddComponent<Tile>(40.0f, 80.0f, "res/Shaders/Basic.shader", "res/Textures/FloorTexture.png");
	/////////////////////Heroes and enemies/////////////////////
	Entity* zubar = HeroCreator::ZubarPrefab(glm::vec3(0.0f, 0.0f, 0.0f));
	stepSM->AddHero(*zubar->GetComponent<Hero>()); //!!!

	Entity* zubar2 = HeroCreator::ZubarPrefab(glm::vec3(0.0f, 55.0f, 0.0f));
	stepSM->AddHero(*zubar2->GetComponent<Hero>()); //!!!

	Entity* enemy1 = EnemyCreator::BasicEnemyPrefab(glm::vec3(400.0f, 680.0f, 0.0f));
	stepSM->AddEnemy(*enemy1->GetComponent<Enemy>()); //!!!

	Entity* enemy2 = EnemyCreator::BasicEnemyPrefab(glm::vec3(1200.0f, 70.0f, 0.0f));
	stepSM->AddEnemy(*enemy2->GetComponent<Enemy>()); //!!!

	Entity* enemy3 = EnemyCreator::BasicEnemyPrefab(glm::vec3(1280.0f, 70.0f, 0.0f));
	stepSM->AddEnemy(*enemy3->GetComponent<Enemy>()); //!!!
	//////////////////////////////////////////////////////////////

	vec.push_back(floor_main1);
	vec.push_back(floor_main2);
	vec.push_back(hallway1);
	vec.push_back(stepSys);
	vec.push_back(zubar);
	vec.push_back(zubar2);
	vec.push_back(enemy1);
	vec.push_back(enemy2);
	vec.push_back(enemy3);
}
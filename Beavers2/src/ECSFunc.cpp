#include "ECSFunc.h"

//////////////////////////// - INFORMATION - ///////////////////////////////
//// 1. Устанавливать координаты всегда числами кратными 10    ////
//// 2. Размеры объектов указывать также числами кратными		////
////    10																////
////////////////////////////////////////////////////////////////////////////
glm::vec4 basicColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

void ECSInit()
{
	/////////////////////Define entities/////////////////////
	Entity& coursor(Manager::addEntity());
	Entity& cam(Manager::addEntity());
	Entity& raycast(Manager::addEntity());
	Entity& stepSys(Manager::addEntity());
	Entity& floor(Manager::addEntity());
	Entity& message(Manager::addEntity());
	Entity& timeManager(Manager::addEntity());
	//////////////////////////////////////////////
	timeManager.AddComponent<Time>();

	StepSysManager* stepSM = stepSys.AddComponent<StepSysManager>();

	raycast.AddComponent<Raycast>();

	coursor.AddComponent<Coursor>();
	
	cam.AddComponent<Transform>(glm::vec3(0.0f));
	cam.AddComponent<MovementComponent>(8.0f);
	cam.AddComponent<CamComponent>();
	///////////////////////////////////////////////////
	


	/////////////////////Heroes and enemies/////////////////////
	stepSM->AddHero(*HeroZubarPrefab(glm::vec3(200.0f, 0.0f, 0.0f))->GetComponent<Hero>()); //!!!
	//stepSM->AddHero(*HeroZubarPrefab(glm::vec3(200.0f, 0.0f, 0.0f))->GetComponent<Hero>()); //!!!

	stepSM->AddEnemy(*BasicEnemyPrefab(glm::vec3(-200.0f, 0.0f, 0.0f))->GetComponent<Enemy>()); //!!!
	//////////////////////////////////////////////////////////////


	/////////////////////Environment/////////////////////
	


	
	floor.AddComponent<Transform>(glm::vec3(0.0f, 0.0f, 0.0f));
	floor.AddComponent<Tile>(1200.0f, 1200.0f, "res/Shaders/Basic.shader", "res/Textures/FloorTexture.png");
}

void ECSStop(std::unique_ptr<Manager> manager)
{
	manager->refresh();
	manager.reset();
}

Entity& CreatObj()
{
	Entity& obj(Manager::addEntity());

	return obj;
}



//some prefabs as functions. Don't know still is it worth it to declare them?
Entity* HeroZubarPrefab(glm::vec3 pos)
{
	Entity* hero(&Manager::addEntity());

	hero->AddComponent<Transform>(pos,
		glm::vec3(50.0f, 50.0f, 1.0f));
	hero->AddComponent<HeroUse>();
	hero->AddComponent<Stamina>(100);
	hero->AddComponent<HP>();
	hero->AddComponent<SpriteComponent>("res/Textures/Zubki.png",
		"res/Shaders/Basic.shader",
		basicColor);
	hero->AddComponent<BoxCollider>(50, 50, true, true);
	hero->AddComponent<Hero>(); 
	hero->AddComponent<Inventory>();
	hero->AddComponent<HeroMov>(10);

	

	return hero;
}

Entity* BasicEnemyPrefab(glm::vec3 pos)
{
	Entity* enemy(&Manager::addEntity());

	enemy->AddComponent<Transform>(pos,
								   glm::vec3(50.0f, 50.0f, 1.0f));
	enemy->AddComponent<EnemyUse>();
	enemy->AddComponent<Stamina>(100);
	enemy->AddComponent<HP>();
	enemy->AddComponent<SpriteComponent>("res/Textures/bobr.png",
		"res/Shaders/Basic.shader",
		basicColor);
	enemy->AddComponent<BoxCollider>(50, 50, true, true);
	enemy->AddComponent<Enemy>(); 
	enemy->AddComponent<EnemyMov>(400.0f, 10);
	

	return enemy;
}
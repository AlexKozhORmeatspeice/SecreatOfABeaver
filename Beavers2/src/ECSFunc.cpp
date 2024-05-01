#include "ECSFunc.h"

//////////////////////////// - INFORMATION - ///////////////////////////////
//// 1. Устанавливать координаты всегда числами кратными 10    ////
//// 2. Размеры объектов указывать также числами кратными		////
////    10																////
////////////////////////////////////////////////////////////////////////////

void ECSInit()
{
	Entity& beaver1(Manager::addEntity());
	Entity& beaver2(Manager::addEntity());

	Entity& enemy(Manager::addEntity());

	Entity& coursor(Manager::addEntity());
	Entity& cam(Manager::addEntity());
	Entity& stepSys(Manager::addEntity());

	StepSysManager* stepSM = stepSys.AddComponent<StepSysManager>();

	coursor.AddComponent<Coursor>();
	
	cam.AddComponent<PositionComponent>(glm::vec3(0, 0, 0));
	cam.AddComponent<MovementComponent>(5.0f);
	cam.AddComponent<CamComponent>();


	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	////
	beaver1.AddComponent<PositionComponent>(glm::vec3(-200.0f, 50.0f, 0.0f));
	beaver1.AddComponent<Stamina>(100);
	beaver1.AddComponent<HP>();
	beaver1.AddComponent<SpriteComponent>("res/Textures/Zubki.png", 
		"res/Shaders/Basic.shader",
		color);
	beaver1.AddComponent<BoxCollider>(50, 50, true, true);
	stepSM->AddHero(beaver1.AddComponent<Hero>()); //!!!
	beaver1.AddComponent<HeroMov>(10);
	////

	////
	beaver2.AddComponent<PositionComponent>(glm::vec3(-50.0f, -100.0f, 0.0f));
	beaver2.AddComponent<Stamina>(100);
	beaver2.AddComponent<HP>();
	beaver2.AddComponent<SpriteComponent>("res/Textures/Zubki.png", 
		"res/Shaders/Basic.shader",
		color);
	beaver2.AddComponent<BoxCollider>(50, 50, true, false);
	stepSM->AddHero(beaver2.AddComponent<Hero>()); //!!!
	beaver2.AddComponent<HeroMov>(10);
	////

	////
	enemy.AddComponent<PositionComponent>(glm::vec3(100.0f, 100.0f, 0.0f));
	enemy.AddComponent<Stamina>(100);
	enemy.AddComponent<HP>();
	enemy.AddComponent<SpriteComponent>("res/Textures/bobr.png",
		"res/Shaders/Basic.shader",
		color);
	enemy.AddComponent<BoxCollider>(50, 50, true, true);
	stepSM->AddEnemy(enemy.AddComponent<Enemy>()); //!!!
	enemy.AddComponent<EnemyMov>(400.0f, 10);
	////
	
	////
	Entity& floor(Manager::addEntity());
	floor.AddComponent<PositionComponent>(glm::vec3(0.0f, 0.0f, 0.0f));
	floor.AddComponent<Tile>(1200.0f, 1200.0f, "res/Shaders/Basic.shader", 
												"res/Textures/FloorTexture.png");
}

void ECSStop(std::unique_ptr<Manager> manager)
{
	manager.reset();
}

Entity& CreatObj()
{
	Entity& obj(Manager::addEntity());

	return obj;
}
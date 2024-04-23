#include "ECSFunc.h"

//////////////////////////// - INFORMATION - ///////////////////////////////
//// 1. Устанавливать координаты всегда числами кратными 10    ////
//// 2. Размеры объектов указывать также числами кратными		////
////    10																////
////////////////////////////////////////////////////////////////////////////


std::unique_ptr<Manager> manager = std::make_unique<Manager>();

std::unique_ptr<Manager> ECSInit()
{
	Entity& beaver1(manager->addEntity());
	Entity& beaver2(manager->addEntity());

	Entity& enemy(manager->addEntity());
	Entity& enemy2(manager->addEntity());

	Entity& coursor(manager->addEntity());
	Entity& cam(manager->addEntity());

	coursor.AddComponent<Coursor>();

	
	cam.AddComponent<PositionComponent>(glm::vec3(0, 0, 0));
	cam.AddComponent<CamComponent>();
	//cam.AddComponent<MovementComponent>(5.0f);


	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	beaver1.AddComponent<PositionComponent>(glm::vec3(0.0f, 0.0f, 0.0f));
	beaver1.AddComponent<Stamina>(100);
	beaver1.AddComponent<SpriteComponent>("res/Textures/soldier.png", 
		"res/Shaders/Basic.shader",
		color);
	beaver1.AddComponent<BoxCollider>(50, 50, true, true);
	beaver1.AddComponent<HeroMov>(10);
	beaver1.AddComponent<Hero>();

	beaver2.AddComponent<PositionComponent>(glm::vec3(-50.0f, 50.0f, 0.0f));
	beaver2.AddComponent<Stamina>(100);
	beaver2.AddComponent<SpriteComponent>("res/Textures/soldier.png", 
		"res/Shaders/Basic.shader",
		color);
	beaver2.AddComponent<BoxCollider>(50, 50, true, false);
	beaver2.AddComponent<HeroMov>(10);
	beaver2.AddComponent<Hero>();

	enemy.AddComponent<PositionComponent>(glm::vec3(100.0f, 100.0f, 0.0f));
	enemy.AddComponent<Stamina>(100);
	enemy.AddComponent<SpriteComponent>("res/Textures/bobr.png",
		"res/Shaders/Basic.shader",
		color);
	enemy.AddComponent<BoxCollider>(50, 50, true, true);
	//enemy.AddComponent<EnemyMov>(150.0, 10);

	
	Entity& floor(manager->addEntity());
	floor.AddComponent<PositionComponent>(glm::vec3(0.0f, 0.0f, 0.0f));
	floor.AddComponent<Tile>(1200.0f, 1200.0f, "res/Shaders/Basic.shader", 
												"res/Textures/FloorTexture.png");

	return std::move(manager);
}

void ECSStop(std::unique_ptr<Manager> manager)
{
	manager.reset();
}

Entity& CreatObj()
{
	Entity& obj(manager->addEntity());

	return obj;
}
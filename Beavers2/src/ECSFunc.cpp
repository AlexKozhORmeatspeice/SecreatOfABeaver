#include "ECSFunc.h"


std::unique_ptr<Manager> manager = std::make_unique<Manager>();

std::unique_ptr<Manager> ECSInit()
{
	Entity& beaver1(manager->addEntity());
	Entity& beaver2(manager->addEntity());
	Entity& beaver3(manager->addEntity());
	Entity& beaver4(manager->addEntity());

	Entity& coursor(manager->addEntity());
	coursor.AddComponent<Coursor>();


	Entity& cam(manager->addEntity());
	cam.AddComponent<PositionComponent>(glm::vec3(0, 0, 0));
	cam.AddComponent<CamComponent>();
	cam.AddComponent<MovementComponent>(5.0f);

	glm::vec4 color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	beaver1.AddComponent<PositionComponent>(glm::vec3(0.0f, 0.0f, 0.0f));
	beaver1.AddComponent<SpriteComponent>("res/Textures/Beaver1.jpg",
		"res/Shaders/Basic.shader",
		color);
	beaver1.AddComponent<BoxCollider>(50, 50, true, true);
	beaver1.AddComponent<HeroMovementComponent>();


	beaver2.AddComponent<PositionComponent>(glm::vec3(-50.0f, 50.0f, 0.0f));
	beaver2.AddComponent<SpriteComponent>("res/Textures/Beaver1.jpg",
		"res/Shaders/Basic.shader",
		color);
	beaver2.AddComponent<BoxCollider>(50, 50, true, false);

	beaver3.AddComponent<PositionComponent>(glm::vec3(50.0f, 80.0f, 0.0f));
	beaver3.AddComponent<SpriteComponent>("res/Textures/Beaver1.jpg",
		"res/Shaders/Basic.shader",
		color);
	beaver3.AddComponent<BoxCollider>(20, 20, true, true);

	beaver4.AddComponent<PositionComponent>(glm::vec3(0.0f, 50.0f, 0.0f));
	beaver4.AddComponent<SpriteComponent>("res/Textures/Beaver1.jpg",
		"res/Shaders/Basic.shader",
		color);

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
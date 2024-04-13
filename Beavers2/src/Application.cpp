#include <iostream>
#include "Render.h"
#include "System.h"
#include "Components.h"

std::unique_ptr<Manager> ECSInit();
void ECSStop(std::unique_ptr<Manager> manager);

int main()
{	
	if (!GameInit() || !RenderInit())
	{
		return 0;
	}

	std::unique_ptr<Manager> manager = ECSInit();
	while (true)
	{
		if (!GameIter(manager))
			break;
		if (!Render(manager))
			break;

		manager->refresh();
	}
	

	ECSStop(std::move(manager));
	GameStop();
	RenderStop();
}



///////////////////////////////////////////////////////// ECS FUNCS ///////////////////////////////////////////////////////////////
std::unique_ptr<Manager> ECSInit()
{
	std::unique_ptr<Manager> manager = std::make_unique<Manager>();
	Entity& beaver1(manager->addEntity());
	Entity& beaver2(manager->addEntity());
	Entity& beaver3(manager->addEntity());
	Entity& beaver4(manager->addEntity());

	Entity& cam(manager->addEntity());

	cam.AddComponent<PositionComponent>(glm::vec3(0, 0, 0));
	cam.AddComponent<CamComponent>();
	//cam.AddComponent<MovementComponent>(5.0f);

	glm::vec4 color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	beaver1.AddComponent<PositionComponent>(glm::vec3(0.0f, 0.0f, 0.0f));
	beaver1.AddComponent<SpriteComponent>("res/Textures/Beaver1.jpg",
		"res/Shaders/Basic.shader",
		color);
	beaver1.AddComponent<BoxCollider>(50, 50, true);
	beaver1.AddComponent<MovementComponent>(5.0f);

	beaver2.AddComponent<PositionComponent>(glm::vec3(-50.0f, 50.0f, 0.0f));
	beaver2.AddComponent<SpriteComponent>("res/Textures/Beaver1.jpg",
		"res/Shaders/Basic.shader",
		color);
	beaver2.AddComponent<BoxCollider>(50, 50, true);

	beaver3.AddComponent<PositionComponent>(glm::vec3(50.0f, 80.0f, 0.0f));
	beaver3.AddComponent<SpriteComponent>("res/Textures/Beaver1.jpg",
		"res/Shaders/Basic.shader",
		color);
	beaver3.AddComponent<BoxCollider>(20, 20, true);

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
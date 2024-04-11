#include <iostream>
#include "Render.h"
#include "System.h"
#include "Components.h"

std::unique_ptr<Manager> ECSInit()
{
	std::unique_ptr<Manager> manager = std::make_unique<Manager>();
	Entity& beaver(manager->addEntity());
	Entity& cam(manager->addEntity());


	cam.AddComponent<PostitionComponent>(glm::vec3(0,0,0));
	cam.AddComponent<CamComponent>();
	
	glm::vec4 color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	beaver.AddComponent<PostitionComponent>(glm::vec3(0, 0, 0));
	beaver.AddComponent<SpriteComponent>("res/Textures/Beaver1.jpg",
		"res/Shaders/Basic.shader",
		color,
		cam.GetComponent<CamComponent>());
	beaver.AddComponent<MovementComponent>();

	return std::move(manager);
}

void ECSStop(std::unique_ptr<Manager> manager)
{
	manager.reset();
}

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
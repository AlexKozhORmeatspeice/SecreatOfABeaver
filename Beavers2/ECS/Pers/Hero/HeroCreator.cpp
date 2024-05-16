#include "HeroCreator.h"


float HeroCreator::standartSizeIcon = 50.0f;
glm::vec4 HeroCreator::basicColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

Entity* HeroCreator::ZubarPrefab(glm::vec3 pos)
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
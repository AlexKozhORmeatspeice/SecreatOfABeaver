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
	hero->AddComponent<HP>(80);
	hero->AddComponent<SpriteComponent>("res/Textures/Char/Zubki.png",
		"res/Shaders/Basic.shader",
		basicColor);
	hero->AddComponent<BoxCollider>(50, 50, true, true);
	hero->AddComponent<Hero>("zubar");
	hero->AddComponent<Inventory>();
	hero->AddComponent<HeroMov>(10);
	//hero->AddComponent<Skill>();

	return hero;
}

Entity* HeroCreator::MotorPrefam(glm::vec3 pos)
{
	Entity* hero(&Manager::addEntity());

	hero->AddComponent<Transform>(pos,
		glm::vec3(50.0f, 50.0f, 1.0f));
	hero->AddComponent<HeroUse>();
	hero->AddComponent<Stamina>(100);
	hero->AddComponent<HP>(100);
	hero->AddComponent<SpriteComponent>("res/Textures/Char/Motor.png",
		"res/Shaders/Basic.shader",
		basicColor);
	hero->AddComponent<BoxCollider>(50, 50, true, true);
	hero->AddComponent<Hero>("motor");
	hero->AddComponent<Inventory>();
	hero->AddComponent<HeroMov>(10);

	return hero;
}

Entity* HeroCreator::NogotPrefab(glm::vec3 pos)
{
	Entity* hero(&Manager::addEntity());

	hero->AddComponent<Transform>(pos,
		glm::vec3(50.0f, 50.0f, 1.0f));
	hero->AddComponent<HeroUse>();
	hero->AddComponent<Stamina>(100);
	hero->AddComponent<HP>(80);
	hero->AddComponent<SpriteComponent>("res/Textures/Char/Nogot.png",
		"res/Shaders/Basic.shader",
		basicColor);
	hero->AddComponent<BoxCollider>(50, 50, true, true);
	hero->AddComponent<Hero>("nogot");
	hero->AddComponent<Inventory>();
	hero->AddComponent<HeroMov>(10);

	return hero;
}

Entity* HeroCreator::HarchokPrefab(glm::vec3 pos)
{
	Entity* hero(&Manager::addEntity());

	hero->AddComponent<Transform>(pos,
		glm::vec3(50.0f, 50.0f, 1.0f));
	hero->AddComponent<HeroUse>();
	hero->AddComponent<Stamina>(100);
	hero->AddComponent<HP>(70);
	hero->AddComponent<SpriteComponent>("res/Textures/Char/Harchok.png",
		"res/Shaders/Basic.shader",
		basicColor);
	hero->AddComponent<BoxCollider>(50, 50, true, true);
	hero->AddComponent<Hero>("harchok");
	hero->AddComponent<Inventory>();
	hero->AddComponent<HeroMov>(10);

	return hero;
}
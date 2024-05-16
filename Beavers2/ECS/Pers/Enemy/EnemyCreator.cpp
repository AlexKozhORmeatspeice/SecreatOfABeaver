#include "EnemyCreator.h"


float EnemyCreator::standartSizeIcon = 50.0f;
glm::vec4 EnemyCreator::basicColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


Entity* EnemyCreator::BasicEnemyPrefab(glm::vec3 pos)
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
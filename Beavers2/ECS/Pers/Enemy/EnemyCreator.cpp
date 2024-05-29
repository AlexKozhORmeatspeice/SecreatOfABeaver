#include "EnemyCreator.h"

float EnemyCreator::standartSizeIcon = 50.0f;
glm::vec4 EnemyCreator::basicColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


float EnemyCreator::meleeAttackRange  = 150.0f;
float EnemyCreator::middleAttackRange = 400.0f;
float EnemyCreator::longAttackRange   = 600.0f;

Entity* EnemyCreator::BasicBeaver(glm::vec3 pos)
{
	Entity* enemy(&Manager::addEntity());

	enemy->AddComponent<Transform>(pos,
		glm::vec3(50.0f, 50.0f, 1.0f));
	enemy->AddComponent<Stamina>(100);
	enemy->AddComponent<HP>(150);
	enemy->AddComponent<SpriteComponent>("res/Textures/Beavers/bobr.png",
		"res/Shaders/Basic.shader",
		basicColor);
	enemy->AddComponent<BoxCollider>(50, 50, true, true);
	enemy->AddComponent<Enemy>();
	enemy->AddComponent<EnemyAttack>(40, meleeAttackRange, 50); //dm, range, cost attack
	enemy->AddComponent<EnemyMov>(10);  //cost move

	return enemy;
}

Entity* EnemyCreator::BeaverThrower(glm::vec3 pos)
{
	Entity* enemy(&Manager::addEntity());

	enemy->AddComponent<Transform>(pos,
		glm::vec3(50.0f, 50.0f, 1.0f));
	enemy->AddComponent<Stamina>(100);
	enemy->AddComponent<HP>(80);
	enemy->AddComponent<SpriteComponent>("res/Textures/Beavers/bobr_soldat.png",
		"res/Shaders/Basic.shader",
		basicColor);
	enemy->AddComponent<BoxCollider>(50, 50, true, true);
	enemy->AddComponent<Enemy>();
	enemy->AddComponent<EnemyAttack>(20, middleAttackRange, 30); //dm, range, cost attack
	enemy->AddComponent<EnemyMov>(15);  //cost move

	return enemy;
}
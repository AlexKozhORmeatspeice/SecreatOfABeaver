#include "ItemCreator.h"
#include "CircleCollider.h"
#include "SpriteComponent.h"
#include "DamageWeapon.h"

float ItemCreator::standartSizeIcon = 30.0f;

float ItemCreator::meleeAttackRange = 150.0f;
float ItemCreator::middleAttackRange = 400.0f;
float ItemCreator::longAttackRange = 600.0f;


DamageWeapon& ItemCreator::CreateKnife(glm::vec3 pos)
{
	Entity* knife(&Manager::addEntity());
	knife->AddComponent<Transform>(pos, glm::vec3(standartSizeIcon));
	knife->AddComponent<CircleCollider>(80.0f, false, false);
	knife->AddComponent<SpriteComponent>("res/Textures/Weapon/finka_nkvd.png");

	DamageWeapon* dmW = new DamageWeapon(50, 50, 10.0f, meleeAttackRange, 0.3f); // dm, cost use, weight, range, time between
	Item* item = static_cast<Item*>(dmW); //use it as an item!!! IT'S A FABRIC METHOD

	knife->AddComponentAsObject<Item, DamageWeapon>(item);

	return *dmW;
}

DamageWeapon& ItemCreator::CreateShotgun(glm::vec3 pos)
{
	Entity* shotgun(&Manager::addEntity());
	shotgun->AddComponent<Transform>(pos, glm::vec3(standartSizeIcon));
	shotgun->AddComponent<CircleCollider>(80.0f, false, false);
	shotgun->AddComponent<SpriteComponent>("res/Textures/Weapon/obrez_samarskiy.png");

	DamageWeapon* dmW = new DamageWeapon(40, 30, 10.0f, meleeAttackRange, 1.0f); // dm, cost use, weight, range, time between
	Item* item = static_cast<Item*>(dmW); //use it as an item!!! IT'S A FABRIC METHOD

	shotgun->AddComponentAsObject<Item, DamageWeapon>(item);

	return *dmW;
}

DamageWeapon& ItemCreator::CreatePistol(glm::vec3 pos)
{
	Entity* pistol(&Manager::addEntity());
	pistol->AddComponent<Transform>(pos, glm::vec3(standartSizeIcon));
	pistol->AddComponent<CircleCollider>(80.0f, false, false);
	pistol->AddComponent<SpriteComponent>("res/Textures/Weapon/shotgun.png");

	DamageWeapon* dmW = new DamageWeapon(10, 20, 10.0f, middleAttackRange, 0.3f); // dm, cost use, weight, range, time between
	Item* item = static_cast<Item*>(dmW); //use it as an item!!! IT'S A FABRIC METHOD

	pistol->AddComponentAsObject<Item, DamageWeapon>(item);

	return *dmW;
}
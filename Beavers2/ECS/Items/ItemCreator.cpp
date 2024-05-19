#include "ItemCreator.h"
#include "CircleCollider.h"
#include "SpriteComponent.h"
#include "DamageWeapon.h"

float ItemCreator::standartSizeIcon = 30.0f;

DamageWeapon& ItemCreator::CreateKnife(glm::vec3 pos)
{
	Entity* knife(&Manager::addEntity());
	knife->AddComponent<Transform>(pos, glm::vec3(standartSizeIcon));
	knife->AddComponent<CircleCollider>(80.0f, false, false);
	knife->AddComponent<SpriteComponent>("res/Textures/knife.png");

	DamageWeapon* dmW = new DamageWeapon(30, 10, 10.0f, 150.0f, 0.3f);
	Item* item = static_cast<Item*>(dmW); //use it as an item!!! IT'S A FABRIC METHOD

	knife->AddComponentAsObject<Item, DamageWeapon>(item);

	return *dmW;
}
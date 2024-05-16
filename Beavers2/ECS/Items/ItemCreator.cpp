#include "ItemCreator.h"
#include "CircleCollider.h"
#include "SpriteComponent.h"
#include "DamageWeapon.h"

float ItemCreator::standartSizeIcon = 30.0f;

Item* ItemCreator::CreateKnife(glm::vec3 pos)
{
	Entity* knife(&Manager::addEntity());
	knife->AddComponent<Transform>(pos, glm::vec3(standartSizeIcon));
	knife->AddComponent<CircleCollider>(80.0f, false, false);
	knife->AddComponent<SpriteComponent>("res/Textures/knife.png");

	Item* item = static_cast<Item*>(new DamageWeapon(30, 10, 10.0f, 150.0f)); //use it as an item!!! IT'S A FABRIC METHOD

	DamageWeapon* weapon = knife->AddComponentAsObject<Item, DamageWeapon>(item);

	return static_cast<Item*>(weapon);
}
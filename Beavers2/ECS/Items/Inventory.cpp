#include "Inventory.h"


void Inventory::init()
{
	nowWeight = 0.0f;

	Entity* knife(&Manager::addEntity()); //TODO : remove after test
	knife->AddComponent<Transform>();
	knife->AddComponent<SpriteComponent>("res/Textures/knife.png");
	DamageWeapon* weapon = knife->AddComponent<DamageWeapon>(30, 10, 10.0f, 150.0f);
	AddItem(weapon);
}
void Inventory::update()
{

}
void Inventory::lastDraw()
{
	Hero* hero = entity->GetComponent<Hero>();
	if (!hero->isChoosed)
	{
		for (auto& button : buttons)
		{
			button->Disable();
		}
		return;
	}

	glm::vec2 drawPoint = itemStartCoords;

	for (auto& button : buttons)
	{
		button->Enable();
		button->SetCoords(drawPoint);
		drawPoint.x += button->width + spacing;
	}
}

void Inventory::AddItem(Item* item)
{
	if ((nowWeight + item->GetWeight()) <= maxWeight)
	{
		Entity& button(Manager::addEntity());
		SpriteComponent* spriteItem = item->entity->GetComponent<SpriteComponent>();

		UIButton* ui_button =  button.AddComponent<UIButton>(glm::vec2(0.0f), spriteItem->GetTexture(), buttonWidth, buttonHeight);
		Weapon* weapon = static_cast<Weapon*>(item);
		if (weapon)
		{
			auto lambda = [weapon]() { weapon->ChangeChoosedStatus(); }; //wtf am i doing ...
			ui_button->AddCall(lambda);
		}

		spriteItem->Disable();
		item->isInInventory = true;

		Hero* hero = entity->GetComponent<Hero>();
		item->SetHero(hero);

		items.push_back(item);
		buttons.push_back(ui_button);

		nowWeight += item->GetWeight();
	}
}
void Inventory::RemoveItem(Item* item)
{
	auto it = std::find(items.begin(), items.end(), item);
	if (it == items.end())
		return;
	SpriteComponent* sprite = item->entity->GetComponent<SpriteComponent>();
	sprite->Enable();

	size_t index = std::distance(items.begin(), it);
	items.erase(it);

	buttons[index]->entity->destroy();
	buttons.erase(buttons.begin() + index); //im not sure that it would work, but maybe?


	nowWeight -= item->GetWeight();
	
	//TODO: drop item as object
	
	
}
#include "Inventory.h"
#include "SpriteComponent.h"
#include "Hero.h"
#include "DamageWeapon.h"

UIIcon* Inventory::background;
UIButton* Inventory::dropItemButton;
int Inventory::m_inventories = 0;

void Inventory::init()
{
    itemStartCoords = glm::vec2(-0.35f, -0.8f);

	m_inventories++;
	nowWeight = 0.0f;
	//some inventory UI
	if (background == nullptr)
	{
		Entity* black(&Manager::addEntity());
		background = black->AddComponent<UIIcon>(glm::vec2(0.0f, -0.6f), "res/Textures/UI/Inventory.png", 1.0f, 0.4f);
	}
	
	if (dropItemButton == nullptr)
	{

	}
	Entity* icon(&Manager::addEntity());
	heroIcon = icon->AddComponent<UIIcon>(glm::vec2(-0.8f, -0.6f),
										  entity->GetComponent<SpriteComponent>()->GetTexture(), //get sprite of hero from entity
										  0.2f, 0.2f);

	Entity* heroText(&Manager::addEntity());
	heroNameTxt = heroText->AddComponent<UIText>(entity->GetComponent<Hero>()->GetName(),
												glm::vec2(-0.94f, -0.92f),
												0.02f);



	//base weapon
	Entity* knife(&Manager::addEntity());
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
		background->Disable();
		heroIcon->Disable();
		heroNameTxt->Disable();

		for (auto& button : buttons)
		{
			button->Disable();
		}
		return;
	}

	glm::vec2 drawPoint = itemStartCoords;
	background->Enable();
	heroIcon->Enable();
	heroNameTxt->Enable();
	for (auto& button : buttons)
	{
		button->SetCoords(drawPoint);
		button->Enable();
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


	SpriteComponent* spriteItem = item->entity->GetComponent<SpriteComponent>();
	Transform* pos = item->entity->GetComponent<Transform>();

	pos->SetPos(entity->GetComponent<Transform>()->GetPos());
	spriteItem->Enable();
	item->isInInventory = false;
}


Inventory::~Inventory()
{
	m_inventories--;

	heroIcon->entity->destroy();
	heroNameTxt->entity->destroy();

	if (m_inventories == 0)
	{
		background->entity->destroy();
		//dropItemButton->entity->destroy();
	}

}
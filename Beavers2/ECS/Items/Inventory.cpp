#include "Inventory.h"
#include "SpriteComponent.h"
#include "Hero.h"
#include "HeroUse.h"
#include "CircleCollider.h"

#include "ItemCreator.h"

Inventory::Inventory()
{
	maxWeight = 30.0f;
	nowWeight = 0.0f;
}

void Inventory::init()
{
	all_items.clear();
	buttons.clear();

    itemStartCoords = glm::vec2(-0.35f, -0.8f);

	CreateUI();

	//base weapon
	AddItem(&ItemCreator::CreateKnife(glm::vec3(0.0f)));
}
void Inventory::update()
{

}
void Inventory::lastDraw()
{
	Hero* hero = entity->GetComponent<Hero>();
	if (!hero->isChoosed)
	{
		DisableUI();
		return;
	}

	EnableUI();
}

void Inventory::AddItem(Item* item)
{
	bool canAdd = nowWeight + item->GetWeight() <= maxWeight;
	if (canAdd)
	{
		Entity& button(Manager::addEntity());
		SpriteComponent* spriteItem = item->entity->GetComponent<SpriteComponent>();

		UIButton* ui_button =  button.AddComponent<UIButton>(glm::vec2(0.0f), spriteItem->GetTexture(), buttonWidth, buttonHeight);

		HeroUse* heroUse = entity->GetComponent<HeroUse>();

		//calls of button
		auto lamSetItem = [item, heroUse, ui_button]()
		{ 
			if (heroUse->GetNowItem() == item)
			{
				heroUse->NoItem();
				ui_button->SetColor(glm::vec4(1.0f)); //basic color
			}
			else
			{
				heroUse->SetItem(item);
				ui_button->SetColor(glm::vec4(250.0f / 255.0f, 218.0f / 255.0f, 94.0f / 255.0f, 1.0f)); //some golden color
			}
		}; //wtf am i doing ...
		auto lambdaOtherItemUnactive = [item, this]()
		{
			DrawOtherItemsUnactive(item);
		}; 
		ui_button->AddCall(lamSetItem);
		ui_button->AddCall(lambdaOtherItemUnactive);
		//calls of button

		spriteItem->Disable();
		item->isInInventory = true;

		Hero* hero = entity->GetComponent<Hero>();
		item->SetHero(hero);

		all_items.push_back(item);
		buttons.push_back(ui_button);

		nowWeight += item->GetWeight();
	}
}
void Inventory::RemoveItem(Item* item)
{
	if (item == nullptr)
		return;

	auto it = std::find(all_items.begin(), all_items.end(), item);
	if (it == all_items.end())
		return;
	SpriteComponent* sprite = item->entity->GetComponent<SpriteComponent>();
	sprite->Enable();

	size_t index = std::distance(all_items.begin(), it);
	all_items.erase(it);

	buttons[index]->entity->destroy();
	buttons.erase(buttons.begin() + index); //im not sure that it would work, but maybe?

	nowWeight -= item->GetWeight();

	entity->GetComponent<HeroUse>()->NoItem(); //disable choosed weapon

	SpriteComponent* spriteItem = item->entity->GetComponent<SpriteComponent>();
	Transform* pos = item->entity->GetComponent<Transform>();

	pos->SetPos(entity->GetComponent<Transform>()->GetPos());
	spriteItem->Enable();
	item->isInInventory = false;
}

void Inventory::TakeFirstNearItem()
{
	Collider* itemColl = entity->GetComponent<BoxCollider>()->GetCollidObj<Item>();
	Item* item = nullptr;
	if (itemColl == nullptr)
		return;
	item = itemColl->entity->GetComponent<Item>();
	if (item == nullptr || item->isInInventory)
		return;
	
	AddItem(item);
}

void Inventory::CreateUI()
{
	Entity* black(&Manager::addEntity());
	background = black->AddComponent<UIIcon>(glm::vec2(0.0f, -0.6f), "res/Textures/UI/Inventory.png", 1.0f, 0.4f);

	Entity* dropItem(&Manager::addEntity());
	dropItemButton = dropItem->AddComponent<UIButton>(glm::vec2(0.83f, -0.8f), "res/Textures/UI/button.png", 0.14f, 0.1f);
	auto lamDropItem = [this]()
	{
		HeroUse* heroUse = this->entity->GetComponent<HeroUse>();
		Item* nowItem = heroUse->GetNowItem();
		RemoveItem(nowItem);
		heroUse->NoItem();
	};
	dropItemButton->AddCall(lamDropItem);

	Entity* dropText(&Manager::addEntity());
	dropItemText = dropText->AddComponent<UIText>("drop\nitem", glm::vec2(0.77f, -0.78f), 0.03f);
	dropItemText->ChangeColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));




	Entity* takeItem(&Manager::addEntity());
	takeItemButton = takeItem->AddComponent<UIButton>(glm::vec2(0.83f, -0.55f), "res/Textures/UI/button.png", 0.14f, 0.1f);
	auto lamTakeItem = [this]()
	{
		TakeFirstNearItem();
	};
	takeItemButton->AddCall(lamTakeItem);

	Entity* takeItemTxt(&Manager::addEntity());
	takeItemText = takeItemTxt->AddComponent<UIText>("take\nitem", glm::vec2(0.77f, -0.53f), 0.03f);
	takeItemText->ChangeColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));




	Entity* icon(&Manager::addEntity());
	heroIcon = icon->AddComponent<UIIcon>(glm::vec2(-0.8f, -0.6f),
		entity->GetComponent<SpriteComponent>()->GetTexture(), //get sprite of hero from entity
		0.2f, 0.2f);


	Entity* heroText(&Manager::addEntity());
	heroNameTxt = heroText->AddComponent<UIText>(entity->GetComponent<Hero>()->GetName(),
		glm::vec2(-0.94f, -0.92f),
		0.02f);
}

void Inventory::EnableUI()
{
	background->Enable();

	heroIcon->Enable();
	heroNameTxt->Enable();

	dropItemButton->Enable();
	dropItemText->Enable();

	takeItemButton->Enable();
	takeItemText->Enable();
	glm::vec2 drawPoint = itemStartCoords;
	for (auto& button : buttons)
	{
		button->SetCoords(drawPoint);
		button->Enable();
		drawPoint.x += button->width + spacing;
	}
}

void Inventory::DisableUI()
{
	background->Disable();

	heroIcon->Disable();
	heroNameTxt->Disable();

	dropItemButton->Disable();
	dropItemText->Disable();

	takeItemButton->Disable();
	takeItemText->Disable();
	for (auto& button : buttons)
	{
		button->Disable();
	}
}

void Inventory::DrawAllItemsUnactive()
{
	for (int i = 0; i < all_items.size(); i++)
	{
		buttons[i]->SetColor(glm::vec4(1.0f));
	}
}

void Inventory::DrawOtherItemsUnactive(Item* item)
{
	for (int i = 0; i < all_items.size(); i++)
	{
		if (all_items[i] == item)
			continue;

		buttons[i]->SetColor(glm::vec4(1.0f));
	}
}


Inventory::~Inventory()
{
	heroIcon->entity->destroy();
	heroNameTxt->entity->destroy();

	dropItemButton->entity->destroy();
	dropItemText->entity->destroy();

	takeItemButton->entity->destroy();
	takeItemText->entity->destroy();
	
	background->entity->destroy();


	while (all_items.size() > 0)
	{
		RemoveItem(all_items[0]);
	}

	buttons.clear();
	all_items.clear();
}
#include "Hero.h"
#include "StepSystemManager.h"

std::vector<Hero*> Hero::heroes;

Hero::Hero()
{
	name = "default";
}

Hero::Hero(const char* heroName)
{
	name = heroName;
}

void Hero::init()
{
	heroes.push_back(this);

	inFight = false;
	isChoosed = false;
	canTakeAction = true;

	hp = entity->GetComponent<HP>();
	stamina = entity->GetComponent<Stamina>();
}

void Hero::update()
{
	if (hp->isDead())
	{
		isChoosed = false;
		canTakeAction = false;
		inFight = false;

		entity->destroy();

		auto it = std::find(heroes.begin(), heroes.end(), this);
		if (it != heroes.end())
			heroes.erase(it);

		Inventory* inv = entity->GetComponent<Inventory>();
		inv->DropAllItems();

		StepSysManager::RefreshList();
		return;
	}

	if(canTakeAction)
		CheckIsChoosed();

	if (!inFight)
	{
		canTakeAction = true;

		hp->Recover();
		stamina->Recover();
	}
}

void Hero::CheckIsChoosed()
{
	int mouseLeftState = GLFWGetKeyMouseState(GLFW_MOUSE_BUTTON_LEFT);
	int mouseRightState = GLFWGetKeyMouseState(GLFW_MOUSE_BUTTON_RIGHT);

	for (Hero* hero : heroes)
	{
		if (mouseLeftState == GLFW_PRESS && Coursor::GetCollisionStatusWith<BoxCollider>(hero->entity))
		{
			hero->isChoosed = true;
			SetOtherNotChoosed(hero);
			break;
		}
	}

	if (!isChoosed)
		return;

	if (mouseRightState == GLFW_PRESS)
	{
		isChoosed = false;
	}
}

void Hero::SetOtherNotChoosed(Hero* exceptHero)
{
	for (Hero* hero : heroes)
	{
		if (hero == exceptHero)
			continue;

		hero->isChoosed = false;
	}
}

Hero::~Hero()
{
	auto it = std::find(heroes.begin(), heroes.end(), this);
	
	if (it != heroes.end())
	{
		heroes.erase(it);
	}
}
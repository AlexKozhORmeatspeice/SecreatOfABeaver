#include "HeroUse.h"

float HeroUse::timeBetweenUse = 0.2f;

void HeroUse::update()
{
	if (item == nullptr)
	{
		return;
	}

	int mouseLeftState = GLFWGetKeyMouseState(GLFW_MOUSE_BUTTON_LEFT);

	glm::vec3 clickPos = Coursor::GetMousePos();
	glm::vec3 heroPos = entity->GetComponent<Transform>()->GetPos();

	Stamina* nowStamina = entity->GetComponent<Stamina>();

	bool enoughtDist = glm::distance(clickPos, heroPos) <= item->GetRange();
	bool enoughStamina = item->GetUseCost() <= nowStamina->GetNowStamina();
	bool gotLeftClick = mouseLeftState == GLFW_PRESS;
	bool canUse = item->CanUse();

	if (enoughtDist && enoughStamina && canUse && gotLeftClick && (Time::GetCurrentTime() - lastTimeUse > timeBetweenUse))
	{
		lastTimeUse = Time::GetCurrentTime();

		nowStamina->UseStamina(item->GetUseCost());
		item->UseItem();
	}
}

void HeroUse::SetItem(Item* nowItem)
{
	item = nowItem;
}
void HeroUse::NoItem()
{
	item = nullptr;
}

Item* HeroUse::GetNowItem()
{
	return item;
}
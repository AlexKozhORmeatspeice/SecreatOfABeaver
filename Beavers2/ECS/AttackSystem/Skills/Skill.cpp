#include "Skill.h"

void Skill::init()
{
	isChoosed = true;

	heroUse = entity->GetComponent<HeroUse>();
	inv = entity->GetComponent<Inventory>();

	lastTimeUse = Time::GetCurrentTime();

	////////////////////////////////////////////////////////
	Entity* icon = &Manager::addEntity();
	button = icon->AddComponent<UIButton>(glm::vec2(-0.8, 0.8), "res/Textures/button.png", 0.1f, 0.1f);
	auto lamSetActive = [this]()
	{
		if (isChoosed)
		{
			isChoosed = false;

		}
		else
		{
			inv->DrawAllItemsUnactive();
			heroUse->NoItem();
			isChoosed = true;
		}
	};

	text = icon->AddComponent<UIText>(txtMessage.c_str(), glm::vec2(-0.6, 0.8), 0.1f);	
}

void Skill::update()
{
	text->ChangeText(txtMessage);
	
	
	if (heroUse->GetNowItem() != nullptr)
	{
		isChoosed = false;
	}

	CheckCanUse();
}

void Skill::CheckCanUse()
{
	int mouseLeftState = GLFWGetKeyMouseState(GLFW_MOUSE_BUTTON_LEFT);

	glm::vec3 clickPos = Coursor::GetMousePos();
	glm::vec3 heroPos = entity->GetComponent<Transform>()->GetPos();

	Stamina* nowStamina = entity->GetComponent<Stamina>();

	bool enoughtDist = glm::distance(clickPos, heroPos) <= range;
	bool enoughStamina = useCost <= nowStamina->GetNowStamina();
	bool gotLeftClick = mouseLeftState == GLFW_PRESS;

	if (enoughtDist && enoughStamina && gotLeftClick && (Time::GetCurrentTime() - lastTimeUse > 0.3f))
	{
		lastTimeUse = Time::GetCurrentTime();

		nowStamina->UseStamina(useCost);
		Attack();
	}
}

Skill::~Skill()
{
	button->entity->destroy();
}
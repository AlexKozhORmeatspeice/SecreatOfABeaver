#include "Weapon.h"

void Weapon::update()
{
	if (!onHero->isChoosed)
	{
		isChoosed = false;
		return;
	}

	if (!isChoosed)
		return;

	int mouseLeftState = GLFWGetKeyMouseState(GLFW_MOUSE_BUTTON_LEFT);

	glm::vec3 clickPos = Coursor::GetMousePos();
	glm::vec3 heroPos = onHero->entity->GetComponent<Transform>()->GetPos();

	Stamina* nowStamina = onHero->entity->GetComponent<Stamina>();

	bool enoughtDist = glm::distance(clickPos, heroPos) <= rangeAttack;
	bool enoughStamina = useCost <= nowStamina->GetNowStamina();
	bool gotLeftClick = mouseLeftState == GLFW_PRESS;

	std::cout << (enoughtDist && enoughStamina) << std::endl;
	if (enoughtDist && enoughStamina && gotLeftClick)
	{
		nowStamina->UseStamina(useCost);
		UseWeapon();
	}
}
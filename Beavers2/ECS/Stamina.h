#pragma once
#include "ECS.h"
#include "Renderer.h"

class Stamina : public Component
{
private:
	unsigned int nowStamina;
	unsigned int maxStamina;

	static const unsigned int cellSize = 50; //in px
public:
	Stamina();
	Stamina(unsigned int nowMaxStamina);

	void init() override;
	void RecoverStamina();
	void UseStaminaToMove(glm::vec3 pos1, glm::vec3 pos2, unsigned int cellMoveCost);

	bool CanMove(glm::vec3 pos1, glm::vec3 pos2, unsigned int cellMoveCost);

	float GetMaxDistMove(unsigned int cellMoveCost);

	inline unsigned int GetCellSize()
	{
		return cellSize;
	}
};
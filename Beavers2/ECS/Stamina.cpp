#include "Stamina.h"

const unsigned int Stamina::cellSize;

Stamina::Stamina()
{
	maxStamina = 100;
}
Stamina::Stamina(unsigned int nowMaxStamina)
{
	maxStamina = nowMaxStamina;
}

void Stamina::init()
{
	nowStamina = maxStamina;
}

void Stamina::RecoverStamina()
{
	nowStamina = maxStamina;
}

void Stamina::UseStaminaToMove(glm::vec3 pos1, glm::vec3 pos2, unsigned int cellMoveCost)
{
	unsigned int cellsCount = glm::distance(pos1, pos2) / cellSize;
	unsigned int stamCostMove = cellsCount * cellMoveCost;

	if (stamCostMove > nowStamina)
	{
		std::cout << "Not enough stamina" << std::endl;
		return;
	}

	nowStamina -= stamCostMove;
}

bool Stamina::CanMove(glm::vec3 pos1, glm::vec3 pos2, unsigned int cellMoveCost)
{
	unsigned int cellsCount = glm::distance(pos1, pos2) / cellSize;
	unsigned int stamCostMove = cellsCount * cellMoveCost;

	return stamCostMove <= nowStamina;
}

float Stamina::GetMaxDistMove(unsigned int cellMoveCost)
{
	unsigned int toMovePoints = nowStamina / cellMoveCost;
	return toMovePoints * cellSize;
}
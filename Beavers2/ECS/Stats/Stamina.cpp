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

void Stamina::Recover()
{
	nowStamina = maxStamina;
}

bool Stamina::UseStamina(unsigned int usedStamina)
{
	if (usedStamina > nowStamina)
	{
		return false;
	}

	nowStamina -= usedStamina;
	return true;
}

unsigned int Stamina::GetNowStamina()
{
	return nowStamina;
}
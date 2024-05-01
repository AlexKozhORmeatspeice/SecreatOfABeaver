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
	void Recover();

	bool UseStamina(unsigned int usedStamina);
	unsigned int GetNowStamina();


	inline unsigned int GetCellSize()
	{
		return cellSize;
	}
};
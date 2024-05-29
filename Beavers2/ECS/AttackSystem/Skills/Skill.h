#pragma once
#include "ECS.h"
#include "UIIcon.h"
#include "SystemMessage.h"
#include "UIButton.h"
#include "HP.h"
#include "Enemy.h"
#include "Inventory.h"
#include "HeroUse.h"

class Skill : public Component
{
private:
	float useCost;
	float range;

	Inventory* inv;
	HeroUse* heroUse;

	UIButton* button;
	
	float lastTimeUse;
	
	bool isChoosed;
protected:
	UIText* text;
	std::string txtMessage;
public:
	Skill()
	{
		txtMessage = "use cost " + std::to_string(useCost);

		useCost = 20.0f;
		range = 150.0f;
	}
	Skill(float _useCost, float _range)
	{
		txtMessage = "use cost " + std::to_string(useCost);

		useCost = _useCost;
		range = _range;
	}

	void init() override;
	void update() override;

	~Skill();

	float GetUseCost()
	{
		return useCost;
	}
protected:
	void CheckCanUse();
	virtual void Attack() {};
};
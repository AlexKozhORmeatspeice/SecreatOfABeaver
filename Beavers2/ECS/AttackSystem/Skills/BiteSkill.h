#pragma once
#include "Skill.h"

class BiteSkill : public Skill
{
private:
	static float damage;
private:
	BiteSkill() : Skill() 
	{
		txtMessage = "now damage " + std::to_string(damage) + "\n" + "use cost " + std::to_string(GetUseCost());
	}

	void Attack() override;
};
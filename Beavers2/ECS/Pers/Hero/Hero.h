#pragma once
#include "ECS.h"

#include "HP.h"
#include "Stamina.h"

#include "Collider.h"

#include "Render.h"
#include "Coursor.h"

class Hero : public Component
{
private:
	const char* name;
	static std::vector<Hero*> heroes;
	Stamina* stamina;
	HP* hp;

public:
	Hero();
	Hero(const char& heroName);

	bool isChoosed;

	bool canTakeAction;
	bool inFight;

	void init() override;
	void update() override;

	inline const char* GetName()
	{
		return name;
	}

	~Hero();
private:
	void CheckIsChoosed();
	void SetOtherNotChoosed(Hero* exceptHero);
};
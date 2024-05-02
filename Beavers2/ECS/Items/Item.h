#pragma once
#include "ECS.h"
#include "Hero.h"

class Item : public Component
{
protected:
	std::string texture;
	Shader* shader;

	Hero* onHero;
	bool isChoosed;
public:
	bool InInventory;

	void init() override;

	void draw() override;
	void SetHero(Hero* newHero);
};
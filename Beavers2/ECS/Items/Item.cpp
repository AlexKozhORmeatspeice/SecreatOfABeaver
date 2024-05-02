#include "Item.h"

void Item::init()
{
	shader = new Shader("Shader/Basic.shader");
	shader->Bind();

	InInventory = false;
	isChoosed = false;
}


void Item::SetHero(Hero* newHero)
{
	onHero = newHero;
}
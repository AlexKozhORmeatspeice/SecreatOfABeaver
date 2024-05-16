#pragma once
#include "ECS.h"
#include "Item.h"

class ItemCreator
{
private:
	static float standartSizeIcon;
public:
	static Item* CreateKnife();
};
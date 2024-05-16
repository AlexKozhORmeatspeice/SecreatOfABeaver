#pragma once
#include "ECS.h"
#include "Components.h"

class HeroCreator
{
private:
	static float standartSizeIcon;
	static glm::vec4 basicColor;

public:
	static Entity* ZubarPrefab(glm::vec3 pos);
};
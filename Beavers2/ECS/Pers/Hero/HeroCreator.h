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
	static Entity* MotorPrefam(glm::vec3 pos);
	static Entity* NogotPrefab(glm::vec3 pos);
	static Entity* HarchokPrefab(glm::vec3 pos);
};
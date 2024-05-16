#pragma once
#include "Components.h"

class EnemyCreator
{
private:
	static float standartSizeIcon;
	static glm::vec4 basicColor;
public:

	static Entity* BasicEnemyPrefab(glm::vec3 pos);
};
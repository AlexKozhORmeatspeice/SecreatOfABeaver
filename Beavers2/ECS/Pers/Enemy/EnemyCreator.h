#pragma once
#include "Components.h"

class EnemyCreator
{
private:
	static float standartSizeIcon;
	static glm::vec4 basicColor;

	static float meleeAttackRange;
	static float middleAttackRange;
	static float longAttackRange;
public:

	static Entity* BasicBeaver(glm::vec3 pos);
	static Entity* BeaverThrower(glm::vec3 pos);
};
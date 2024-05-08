#pragma once
#include "Render.h"
#include "Components.h"

void ECSInit();
void ECSStop(std::unique_ptr<Manager> manager);

Entity* HeroZubarPrefab(glm::vec3 pos);
Entity* BasicEnemyPrefab(glm::vec3 pos);

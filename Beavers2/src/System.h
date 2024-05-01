#pragma once
#include "Components.h"

bool GameInit();
bool GameIter(std::unique_ptr<Manager> & manager);
void GameStop();
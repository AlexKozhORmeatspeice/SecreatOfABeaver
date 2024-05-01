#pragma once
#include "Render.h"
#include "Components.h"

void ECSInit();
void ECSStop(std::unique_ptr<Manager> manager);
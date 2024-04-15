#pragma once

#include "Render.h"
#include "Components.h"

std::unique_ptr<Manager> ECSInit();
void ECSStop(std::unique_ptr<Manager> manager);


Entity& CreatObj();
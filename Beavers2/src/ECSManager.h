#pragma once
#include "Components.h"

static Manager manager;
static auto& beaver(manager.addEntity());
static auto& cam(manager.addEntity());

bool ECSInit();

void ECSStop();
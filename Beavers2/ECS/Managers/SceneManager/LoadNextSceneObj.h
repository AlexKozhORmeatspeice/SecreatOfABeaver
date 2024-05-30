#pragma once
#include "ECS.h"
#include "Collider.h"
#include "Inventory.h"
#include "SceneManager.h"
class LoadNextScene : public Component
{
private:
	Collider* coll;
public:
	void init() override;
	void update() override;
};
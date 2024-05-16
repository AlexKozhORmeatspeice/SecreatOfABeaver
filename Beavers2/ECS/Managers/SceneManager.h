#pragma once
#include "ECS.h"

class SceneManager : public Component
{
private:
	int nowScene;

public:

	void init() override;
};
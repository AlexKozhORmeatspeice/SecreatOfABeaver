#pragma once
#include "ECS.h"
#include "Components.h"
#include "HeroCreator.h"
#include "EnemyCreator.h"
#include "ItemCreator.h"

class SceneManager : public Component
{
private:
	static int nowScene;
	static std::vector<std::vector<Entity*>& (*)()> scenesFuncs; //not the best, but...I was lazy to do something smarter (look for functions in cpp
	static std::vector<Entity*> currentEntities;
public:

	void init() override;

	static void LoadScene(int n);
	static void LoadNextScene();
	static void ReloadScene();

private:
	static void ClearScene();
};
#include "LoadNextSceneObj.h"

void LoadNextScene::init()
{
	coll = entity->GetComponent<BoxCollider>();
}

void LoadNextScene::update()
{
	Collider* collInv = coll->GetCollidObj<Inventory>();
	Inventory* inv = nullptr;
	if (collInv != nullptr)
	{
		inv = collInv->entity->GetComponent<Inventory>();
	}

	if (inv != nullptr && inv->GotKey())
	{
		SceneManager::LoadNextScene();
	}
}

#pragma once
#include "ECS.h"

#include "Collider.h"
#include "BoxCollider.h"

#include "PositionComponent.h"
#include "Renderer.h"



class Coursor : public Component
{
private:
	static Entity* checkBox;
	static Transform* posBox;

	static glm::vec3 mousePos;
	static glm::vec2 normMousePos;

public:
	static bool isOnUI;

	void update() override;
	void init() override;

	template <typename T>
	static inline bool GetCollisionStatusWith(Entity* collider);

	template <typename T>
	static inline bool GetCollisionStatus();

	template <typename T>
	static inline T* GetCollision();

	static inline glm::vec3 GetMousePos()
	{
		return mousePos;
	}

	static inline glm::vec2 GetNormalizedMousePos()
	{
		return normMousePos;
	}
	~Coursor();
};

template <typename T>
bool Coursor::GetCollisionStatusWith(Entity* collider)
{
	if (isOnUI)
		return false;

	return checkBox->GetComponent<BoxCollider>()->IsColllidWith<T>(collider);
}

template <typename T>
bool Coursor::GetCollisionStatus()
{
	bool isCollide = checkBox->GetComponent<BoxCollider>()->IsCollideWithTrigger();
	return isCollide;
}

template <typename T>
T* Coursor::GetCollision()
{
	Collider* boxCollider = checkBox->GetComponent<BoxCollider>()->GetCollidObj<T>();
	if (boxCollider != nullptr)
	{
		return boxCollider->entity->GetComponent<T>();
	}
	else
	{
		return nullptr;
	}
	
}
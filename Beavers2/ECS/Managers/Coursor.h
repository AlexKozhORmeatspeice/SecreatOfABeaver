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
	static PositionComponent* posBox;

	static glm::vec3 mousePos;
public:
	void update() override;
	void init() override;

	template <typename T>
	static inline bool GetCollision(Entity* collider);

	static inline glm::vec3 GetMousePos()
	{
		return mousePos;
	}

	~Coursor();
};

template <typename T>
bool Coursor::GetCollision(Entity* collider)
{
	const Collider* coll1 = collider->GetComponent<T>();
	const Collider* coll2 = checkBox->GetComponent<BoxCollider>()->GetColllidObj();

	if (coll1 != nullptr && coll2 != nullptr)
	{
		return coll1 == coll2;
	}

	return false;
}
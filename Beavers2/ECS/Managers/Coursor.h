#pragma once
#include "Collider.h"
#include "BoxCollider.h"

#include "Components.h"
#include "Renderer.h"


class Coursor : public Component
{
private:
	static Entity* checkBox;
	static std::shared_ptr<PositionComponent> posBox;

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
};

template <typename T>
bool Coursor::GetCollision(Entity* collider)
{
	const Collider* coll1 = collider->GetComponent<T>().get();
	const Collider* coll2 = checkBox->GetComponent<BoxCollider>()->GetColllidObj();

	if (coll1 != nullptr && coll2 != nullptr)
	{
		return coll1 == coll2;
	}

	std::cout << "NULL POINTER" << std::endl;

	return false;
}
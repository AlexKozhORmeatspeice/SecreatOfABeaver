#pragma once
#include "PositionComponent.h"
#include "cmath"

class Collider : public Component
{
protected:
	static std::vector<Collider*> AllColliders;
	Transform* pos;

	bool drawingColliders = true; // to test param
	bool isTrigger; //true - can react with others, false - cant
	bool isMoveble; //can be moved
	float checkDist;

	std::vector<Collider*> collisionObjs;

	bool getCol;
	bool getColWithTrigger;
public:
	std::vector<glm::vec3> flatVectors;
	Collider();
	
	void update() override;
	void lastUpdate() override;

	template <typename T> bool IsColllidWith(Entity* collider);
	template <typename T> Collider* GetCollidObj();

	bool GetIsTrigger();
	float GetCheckDist();

	bool inline IsCollide()
	{
		return getCol;
	}

	bool inline IsCollideWithTrigger()
	{
		return getColWithTrigger;
	}

	~Collider();
protected:
	virtual bool CheckCollision()   = 0;
	virtual void ResolveColision()  = 0;
	virtual void initVecPositions() = 0;

	void GetMinMaxDotProduct(std::vector<glm::vec3> vertices, glm::vec3 normal, float& min, float& max);
};

template <typename T> 
bool Collider::IsColllidWith(Entity* collider)
{
	const Collider* coll1 = collider->GetComponent<T>();

	if (coll1 != nullptr)
	{
		for (auto& coll2 : collisionObjs)
		{
			if (coll2 == coll1)
			{
				return true;
			}
		}
	}

	return false;
}

template <typename T> 
Collider* Collider::GetCollidObj()
{
	for (auto& coll : collisionObjs)
	{
		if (coll->entity->HasComponent<T>())
		{
			return coll;
		}
	}

	return nullptr;
}
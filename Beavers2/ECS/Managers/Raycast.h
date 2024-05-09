#pragma once
#include "ECS.h"
#include "Render.h"
#include "PositionComponent.h"
#include "CircleCollider.h"
#include "Enemy.h"
#include "BoxCollider.h"

class Raycast : public Component
{
private:
	static CircleCollider* circleCollider;

public:
	void init() override;

	template <typename T> 
	static bool CheckCollision(glm::vec3 startPoint, glm::vec3 dir, float length, const Entity* exceptEntity); //need to change exceptEntity to bitmask or something

	template <typename T>
	static bool CheckCollision(glm::vec3 startPoint, glm::vec3 dir, const Entity* exceptEntity);

	static glm::vec3 GetPointOfCollision(glm::vec3 startPoint, glm::vec3 dir, const Entity* exceptEntity);

	~Raycast();
};

/// <summary>
/// Just moving circle to check collision
/// stPoint: (1)->(2)->(3)->(4)->(5)->(6) :endPoint
/// </summary>

template <typename T>
bool Raycast::CheckCollision(glm::vec3 startPoint, glm::vec3 dir, float length, const Entity* exceptEntity)
{
	float speedInter = 0.1f;

	Transform* circleTrans = circleCollider->entity->GetComponent<Transform>();
	for (float t = 0.0f; t <= 1.0f; t += speedInter)
	{
		glm::vec3 newPos = startPoint + dir*(length*t);
		
		circleTrans->SetPos(newPos);
		circleCollider->update();
		circleCollider->lastUpdate();
		

		Collider* selfCollision = circleCollider->GetCollidObj<BoxCollider>();
		if (selfCollision != nullptr && selfCollision->entity == exceptEntity)
		{
			continue;
		}

		if (circleCollider->IsCollideWithTrigger())
		{
			Collider* coll = circleCollider->GetCollidObj<T>();
			return (coll != nullptr);
		}
	}
	
	return false;
}

template <typename T>
bool Raycast::CheckCollision(glm::vec3 startPoint, glm::vec3 dir, const Entity* exceptEntity)
{
	float speedInter = 0.1f;

	Transform* circleTrans = circleCollider->entity->GetComponent<Transform>();

	for (float t = 0.0f; t <= 1.1f; t += speedInter)
	{
		glm::vec3 newPos = startPoint + dir * t;
		newPos.z = 0.0f;

		circleTrans->SetPos(newPos);
		circleCollider->update();
		circleCollider->lastUpdate();


		Collider* selfCollision = circleCollider->GetCollidObj<BoxCollider>();
		if (selfCollision != nullptr && selfCollision->entity == exceptEntity)
		{
			continue;
		}

		if (circleCollider->IsCollideWithTrigger())
		{
			Collider* coll = circleCollider->GetCollidObj<T>();
			return (coll != nullptr);
		}
	}
	
	return false;
}
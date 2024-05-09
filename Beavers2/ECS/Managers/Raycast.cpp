#include "Raycast.h"

CircleCollider* Raycast::circleCollider;

void Raycast::init()
{
	Entity& circle = Manager::addEntity();
	circle.AddComponent<Transform>();
	circleCollider = circle.AddComponent<CircleCollider>(5.0f, false, false);
}


Raycast::~Raycast()
{
	circleCollider->entity->destroy();
}

glm::vec3 Raycast::GetPointOfCollision(glm::vec3 startPoint, glm::vec3 dir, const Entity* exceptEntity)
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
			Collider* coll = circleCollider->GetCollidObj<BoxCollider>();
			if (coll != nullptr)
			{
				return newPos;
			}
		}
	}

	return startPoint + dir;
}
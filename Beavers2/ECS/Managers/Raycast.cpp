#include "Raycast.h"


CircleCollider* Raycast::circleCollider;

void Raycast::init()
{
	Entity& circle = Manager::addEntity();
	circle.AddComponent<Transform>();
	circleCollider = circle.AddComponent<CircleCollider>(10.0f, false, false);
}


Raycast::~Raycast()
{
	circleCollider->entity->destroy();
}
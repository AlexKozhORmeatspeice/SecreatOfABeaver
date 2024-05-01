#include "Collider.h"
std::vector<Collider*> Collider::AllColliders;

Collider::Collider()
{
	collisionObjs.clear();
	AllColliders.push_back(this);
}

void Collider::update()
{
	initVecPositions();
	getCol = CheckCollision();

	if (getCol && isTrigger && (collisionObjs.size() != 0))
		ResolveColision();
}

void Collider::GetMinMaxDotProduct(std::vector<glm::vec3> vertices, glm::vec3 normal, float& min, float& max)
{
	max = 0;
	min = 1 << 30;
	for (glm::vec3& vertex : vertices)
	{
		float prod = glm::dot(vertex, normal);

		min = std::min(min, prod);
		max = std::max(max, prod);
	}
}

bool Collider::GetIsTrigger()
{
	return isTrigger;
}
float Collider::GetCheckDist()
{
	return checkDist;
}

Collider::~Collider()
{
	auto it = std::find(AllColliders.begin(), AllColliders.end(), this);
	if (it != AllColliders.end())
		AllColliders.erase(it);
}
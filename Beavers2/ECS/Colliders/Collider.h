#pragma once
#include "PositionComponent.h"
#include "cmath"

class Collider : public Component
{
protected:
	static std::vector<Collider*> AllColliders;
	std::shared_ptr<PositionComponent> pos;

	bool drawingColliders = true; // to test param
	bool isTrigger; //true - can react with others, false - cant
	bool isMoveble; //can be moved
	float checkDist;

	Collider* collisionObj;

	bool getCol;
public:
	std::vector<glm::vec3> flatVectors;
	Collider();
	
	void update() override;

	Collider* GetColllidObj();
	bool GetIsTrigger();
	float GetCheckDist();

	~Collider();
protected:
	virtual bool CheckCollision()   = 0;
	virtual void ResolveColision()  = 0;
	virtual void initVecPositions() = 0;

	void GetMinMaxDotProduct(std::vector<glm::vec3> vertices, glm::vec3 normal, float& min, float& max);
};
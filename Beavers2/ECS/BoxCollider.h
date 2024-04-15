#pragma once
#include "Components.h"
#include "cmath"

class BoxCollider : public Component
{
private:
	static std::vector<BoxCollider*> AllColliders;
	float checkDist;

	BoxCollider* collisionObj;
	std::shared_ptr<PositionComponent> pos;
	
	bool drawingColliders = true;
	bool isTrigger; //true - can react with others, false - cant
	bool isMoveble; //can be moved
	float width;
	float height;

	float vertices[8] = {
		-10.0f, -10.0f,
		 10.0f, -10.0f,
		 10.0f,  10.0f,
		-10.0f,  10.0f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};
	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexArray* va;
	Shader* shader;
	Renderer renderer;

	glm::mat4 m_MVP;
public:
	std::vector<glm::vec3> flatVectors;

	BoxCollider();
	BoxCollider(float nowWidth, float nowHeigt, bool nowIsTrigger, bool moveable);

	void init() override;
	void update() override;
	void draw() override;


	BoxCollider* GetColllidObj();
	bool GetIsTrigger();
	float GetCheckDist();
	~BoxCollider();
private:
	bool CheckCollision();
	void ResolveColision();

	void GetMinMaxDotProduct(std::vector<glm::vec3> vertices, glm::vec3 normal, float& min, float& max);
	void initVecPositions();
};
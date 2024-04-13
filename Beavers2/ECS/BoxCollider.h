#pragma once
#include "Components.h"

class BoxCollider : public Component
{
private:
	static std::vector<BoxCollider*> AllColliders;


	std::shared_ptr<PostitionComponent> pos;
	bool drawingColliders = true;
	bool isTrigger; //means that it can resolve collision

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
	BoxCollider(float nowWidth, float nowHeigt, bool nowIsTrigger);

	void init() override;
	void update() override;
	void draw() override;


	~BoxCollider();
private:
	bool CheckCollision();
	void ResolveColision();

	void GetMinMaxDotProduct(std::vector<glm::vec3> vertices, glm::vec3 normal, float& min, float& max);
	void initVecPositions();
};
#pragma once
#include "cmath"
#include "Renderer.h"
#include "Collider.h"
#include "CamComponent.h"


class BoxCollider : public Collider
{
private:
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
	BoxCollider();
	BoxCollider(float nowWidth, float nowHeigt, bool nowIsTrigger, bool moveable);

	void init() override;
	void draw() override;

	~BoxCollider();
protected:
	bool CheckCollision() override;
	void ResolveColision() override;

	void initVecPositions() override;
};
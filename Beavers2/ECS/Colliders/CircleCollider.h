#pragma once
#include "Collider.h"
#include "Renderer.h"
#include "CamComponent.h"
#include "Render.h"
class CircleCollider : public Collider
{
private:
	float vertices[16] = {
		-10.0f, -10.0f, 0.0f, 0.0f,
		 10.0f, -10.0f, 1.0f, 0.0f,
		 10.0f,  10.0f, 1.0f, 1.0f,
		-10.0f,  10.0f, 0.0f, 1.0f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexArray* va;
	Shader* shader;

	glm::mat4 m_MVP;
public:
	CircleCollider();
	CircleCollider(float radius, bool nowIsTrigger, bool moveable);
	
	void init() override;
	void draw() override;
	
	~CircleCollider();
protected:
	bool CheckCollision() override;
	void ResolveColision() override;
	void initVecPositions() override;

};
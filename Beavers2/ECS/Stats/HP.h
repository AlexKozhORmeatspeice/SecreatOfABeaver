#pragma once
#include "ECS.h"
#include "Renderer.h"
#include "PositionComponent.h"

class HP : public Component
{
private:
	float vertices[16] = {
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexArray* va;
	Shader* shader;
	Texture* texture;

	glm::mat4 m_MVP;

	Transform* pos;
	int maxHP = 100;
	int nowHP;
public:
	HP();
	HP(int nowMaxHP);

	void init() override;
	void draw() override;

	void GetDamage(int useHP);
	void Recover();
	bool isDead();

	~HP();
};
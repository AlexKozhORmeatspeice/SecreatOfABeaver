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
	unsigned int maxHP = 100;
	unsigned int nowHP;
public:
	HP();
	HP(unsigned int nowMaxHP);

	void init() override;
	void draw() override;

	void GetDamage(unsigned int useHP);
	void Recover();
	bool isDead();

	~HP();
};
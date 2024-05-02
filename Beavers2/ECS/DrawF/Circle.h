#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "CamComponent.h"
#include "Renderer.h"

class Circle : public Component
{
private:
	bool isActive;
	Transform* transform;

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
	float radius;

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexArray* va;
	Shader* shader;

	glm::mat4 m_MVP;
public:
	Circle();
	Circle(float nowRadius);

	void init() override;
	void draw() override;
	

	~Circle();

	inline void Activate()
	{
		isActive = true;
	}
	inline void Unactivate()
	{
		isActive = false;
	}

	void SetColor(glm::vec4 color);
	void SetRadius(float newRadius);
};
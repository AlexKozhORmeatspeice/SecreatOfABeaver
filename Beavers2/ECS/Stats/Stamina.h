#pragma once
#include "ECS.h"
#include "Renderer.h"
#include "PositionComponent.h"
#include "CamComponent.h"

class Stamina : public Component
{
private:
	unsigned int nowStamina;
	unsigned int maxStamina;

	static const unsigned int cellSize = 50; //in px

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
public:
	Stamina();
	Stamina(unsigned int nowMaxStamina);

	void init() override;
	void draw() override;
	void Recover();

	bool UseStamina(unsigned int usedStamina);
	unsigned int GetNowStamina();


	inline unsigned int GetCellSize()
	{
		return cellSize;
	}
};
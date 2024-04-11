#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "CamComponent.h"
#include "Renderer.h"

class SpriteComponent : public Component
{
private:
	std::shared_ptr<PostitionComponent> pos;
	std::shared_ptr<CamComponent> activeCam;
	glm::mat4 m_MVP;

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexArray* va;
	Shader* shader_basic;
	Texture* texture;
	Renderer renderer;

	glm::vec4 color;

	float postitions[4 * 4] = {
	 -50.0f, -50.0f, 0.0f, 0.0f,
	  50.0f, -50.0f, 1.0f, 0.0f,
	  50.0f,  50.0f, 1.0f, 1.0f,
	 -50.0f,  50.0f, 0.0f, 1.0f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};
public:

	SpriteComponent(const char* pathTexture, const char* pathShader, glm::vec4 nowColor, std::shared_ptr<CamComponent> nowCam);

	void SetNewColor(glm::vec4 newColor);

	void init() override;

	void update() override;
	void draw() override;

	~SpriteComponent();
};

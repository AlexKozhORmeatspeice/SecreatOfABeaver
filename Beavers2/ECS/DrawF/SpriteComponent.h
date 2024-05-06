#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "CamComponent.h"
#include "Renderer.h"

class SpriteComponent : public Component
{
private:
	Transform* transform;
	CamComponent* activeCam;
	glm::mat4 m_MVP;

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexArray* va;
	Shader* shader_basic;

	const char* texture_path;
	Texture* texture;

	glm::vec4 color;

	float postitions[4 * 4] = {
	 -1.0f, -1.0f, 0.0f, 0.0f,
	  1.0f, -1.0f, 1.0f, 0.0f,
	  1.0f,  1.0f, 1.0f, 1.0f,
	 -1.0f,  1.0f, 0.0f, 1.0f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};
public:
	bool isDisabled;
	SpriteComponent(const char* pathTexture);
	SpriteComponent(const char* pathTexture, glm::vec4 nowColor);
	SpriteComponent(const char* pathTexture, const char* pathShader, glm::vec4 nowColor);

	void SetNewColor(glm::vec4 newColor);

	void init() override;

	void update() override;
	void draw() override;

	void inline Disable()
	{
		isDisabled = true;
	}

	void inline Enable()
	{
		isDisabled = false;
	}
	
	const char* GetTexture()
	{
		return texture_path;
	}
	~SpriteComponent();
};

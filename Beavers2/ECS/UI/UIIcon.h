#pragma once
#include "ECS.h"
#include "Render.h"
#include "Renderer.h"
#include "UIElement.h"

/// <summary>
/// works with opengl coords (-1 to 1)
/// </summary>
class UIIcon : public UIElement
{
protected:
	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexArray* va;
	Shader* shader_basic;
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
	UIIcon();
	UIIcon(glm::vec2 newCoords, const char* pathTexture, const char* pathShader, float nowWidth, float nowHeight);
	UIIcon(glm::vec2 newCoords, const char* pathTexture, float nowWidth, float nowHeight);

	void init() override;
	void lastDraw() override;
	
	virtual void SetColor(glm::vec4 newColor)
	{
		color = newColor;
	}
	~UIIcon();
};
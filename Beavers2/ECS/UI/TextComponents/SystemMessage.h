#pragma once
#include <iostream>
#include "ECS.h"
#include "FontSheet.h"
#include "UIElement.h"

class UIText : public UIElement
{
private:
	float space_x = 1 / 32.0f;
	float space_y = 1 / 32.0f;
	float symbolSize;
	std::string message;

	IndexBuffer* ib;
	VertexBuffer* vb;
	VertexArray* va;
	Shader* shader;
	Texture* texture;
	float vertices[4 * 4] = {
	 -1.0f, -1.0f, 0.0f, 0.0f,
	  1.0f, -1.0f, 1.0f, 0.0f,
	  1.0f,  1.0f, 1.0f, 1.0f,
	 -1.0f,  1.0f, 0.0f, 1.0f
	};

	unsigned int indexes[6] = {
		0, 1, 2,
		2, 3, 0
	};

public: 
	UIText(std::string cur_message, glm::vec2 nowCoords, float size);
	void lastDraw() override;
	void init() override;

	void ChangeColor(glm::vec4 color);

	void ChangeText(std::string msg)
	{
		message = msg;
	}
	~UIText();
};
#include "SystemMessage.h"

UIText::UIText(std::string cur_message, glm::vec2 nowCoords, float size)
{
	message = cur_message;
	coords = nowCoords;
	symbolSize = size;

	std::string mode = "CLAMP";
	texture = new Texture("res/Fonts/Verdana.png", mode);
}
void UIText::init()
{
	vb = new VertexBuffer(vertices, 4 * 4 * sizeof(float));
	ib = new IndexBuffer(indexes, 6);
	va = new VertexArray;

	
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);

	shader = new Shader("res/Shaders/Text.shader");
	shader->Bind();

	texture->Bind();
	shader->SetUniform1i("u_Texture", 0);

	shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	shader->Unbind();
	vb->Unbind();
	ib->Unbind();
	va->Unbind();
	texture->Unbind();
}
void UIText::lastDraw()
{
	if (!enabled)
		return;

	shader->Bind();
	texture->Bind();
	int indX = 0;
	int indY = 0;
	for (auto c = message.begin(); c != message.end(); c++)
	{
		shader->Bind();
		char symb = *c;
		
		int y = 17 - (symb >> 4);
		int x = symb & 0b1111;
		float textureScale = 1/16.0f;
		if (symb == '\n')
		{
			indY++;
			indX = 0;
			continue;
		}

		//texture coords
		glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(textureScale, textureScale, 1.0f));
		glm::mat4 Translate = glm::translate(glm::mat4(1.0f), glm::vec3(x*textureScale, y * textureScale, 0.0f));

		glm::mat4 Tr_a_Sc = Translate * Scale;
		shader->SetUniformMat4f("u_SCALE_AND_TRANSLATE", Tr_a_Sc);

		//vertex coords
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(coords.x + indX*(space_x + (symbolSize / 2.0f) * (symb != ' ')),
																	coords.y - indY*(space_y + (symbolSize / 2.0f)),
																	-0.1f));

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(symbolSize, symbolSize, 1.0f));

		glm::mat4 m_MS = model * scale;

		shader->SetUniformMat4f("u_MVP", m_MS);

		Renderer::Draw(*va, *ib, *shader);
		indX++;
		shader->Unbind();
	}
	texture->Unbind();
}

void UIText::ChangeColor(glm::vec4 color)
{
	shader->Bind();
	shader->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
	shader->Unbind();
}
UIText::~UIText()
{
	delete vb;
	delete ib;
	delete va;
	delete shader;
	delete texture;
}
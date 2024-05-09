#include "SystemMessage.h"

SystemMessage::SystemMessage(std::string cur_message, const char* pathTexture)
{
	message = cur_message;

	std::string mode = "CLAMP";
	texture = new Texture(pathTexture, mode);
}
void SystemMessage::init()
{
	vb = new VertexBuffer(vertices, 4 * 4 * sizeof(float));
	ib = new IndexBuffer(indexes, 6);
	va = new VertexArray;

	coords = glm::vec2(0.0f);
	
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
void SystemMessage::draw()
{
	shader->Bind();
	texture->Bind();
	int ind = 0;
	for (auto c = message.begin(); c != message.end(); c++)
	{
		shader->Bind();
		char symb = *c;
		int x = symb >> 4;
		int y = symb & 0b1111;
		//texture coords
		glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(1 / 16.0f, 1 / 16.0f, 1.0f));
		glm::mat4 Translate = glm::translate(glm::mat4(1.0f), glm::vec3(x/16.f, y/16.f, 0.2f));

		glm::mat4 TAS = Translate * Scale;
		shader->SetUniformMat4f("u_SCALE_AND_TRANSLATE", TAS);

		//vertex coords
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(coords.x + ind*space_x, 0.0f, 0.0f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1 / 16.0f, 1 / 16.0f, 1.0f));

		glm::mat4 m_MS = model * scale;

		shader->SetUniformMat4f("u_MVP", m_MS);

		Renderer::Draw(*va, *ib, *shader);
		ind++;
		shader->Unbind();
	}
	texture->Unbind();
}

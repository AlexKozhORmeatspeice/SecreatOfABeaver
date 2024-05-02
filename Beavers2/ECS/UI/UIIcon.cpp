#include "UIIcon.h"

UIIcon::UIIcon()
{
	coords = glm::vec2(0.0f);
	width = 0.1f;
	height = 0.1f;

	const std::string mode = "CLAMP";
	texture = new Texture("res/Textures/button.png", mode);
}

UIIcon::UIIcon(glm::vec2 newCoords, const char* pathTexture, float nowWidth, float nowHeight)
{
	coords = newCoords;
	width = nowWidth;
	height = nowHeight;

	const std::string mode = "CLAMP";
	texture = new Texture(pathTexture, mode);
}

void UIIcon::init()
{
	vb = new VertexBuffer(postitions, 4 * 4 * sizeof(float));
	ib = new IndexBuffer(indices, 6);
	va = new VertexArray;

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);

	shader_basic = new Shader("res/Shaders/Basic.shader");
	shader_basic->Bind();
	
	texture->Bind();
	shader_basic->SetUniform1i("u_Texture", 0);

	color = glm::vec4(1.0f);
	shader_basic->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);

	shader_basic->Unbind();
	vb->Unbind();
	ib->Unbind();
	va->Unbind();
	texture->Unbind();
}

void UIIcon::update()
{
	
}

void UIIcon::lastDraw()
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(coords.x, coords.y, 0.0f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(width, height, 1.0f));

	glm::mat4 m_MS = model * scale;

	shader_basic->Bind();
	shader_basic->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
	shader_basic->SetUniformMat4f("u_MVP", m_MS);
	shader_basic->Unbind();

	texture->Bind();
	Renderer::Draw(*va, *ib, *shader_basic);
	texture->Unbind();
}



UIIcon::~UIIcon()
{
	delete ib;
	delete vb;
	delete va;
	delete shader_basic;
	delete texture;
}

#include "Stamina.h"

const unsigned int Stamina::cellSize;

Stamina::Stamina()
{
	maxStamina = 100;
}
Stamina::Stamina(unsigned int nowMaxStamina)
{
	maxStamina = nowMaxStamina;
}

void Stamina::init()
{
	pos = entity->GetComponent<Transform>();

	shader = new Shader("res/Shaders/BarSlider.shader");
	shader->Bind();

	const std::string mode = "CLAMP";
	texture = new Texture("res/Textures/UI/HPBar.png", mode);
	texture->Bind();
	shader->SetUniform1i("u_Texture", 0);

	m_MVP = glm::mat4(1.0f);

	shader->Bind();
	texture->Bind();
	vb = new VertexBuffer(vertices, 4 * 4 * sizeof(float));
	ib = new IndexBuffer(indices, 6);
	va = new VertexArray;

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);

	shader->SetUniform1i("u_Texture", 0);
	shader->SetUniform4f("u_FirstColor", 54.0/255.0, 1.0, 1.0, 1.0);

	vb->Unbind();
	ib->Unbind();
	va->Unbind();
	shader->Unbind();
	texture->Unbind();

	nowStamina = maxStamina;
}

void Stamina::draw()
{
	glm::mat4 proj = CamComponent::GetProj();
	glm::mat4 view = glm::translate(glm::mat4(1.0f), -CamComponent::GetPos());
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos->GetPos().x,
									 pos->GetPos().y + pos->GetScale().y * 2.0f,
									 pos->GetPos().z));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), pos->GetScale());

	m_MVP = proj * view * model * scale;
	shader->Bind();

	shader->SetUniformMat4f("u_MVP", m_MVP);
	shader->SetUniform1f("now", (float)nowStamina);
	shader->SetUniform1f("max", (float)maxStamina);

	texture->Bind();
	Renderer::Draw(*va, *ib, *shader);
	texture->Unbind();
	shader->Unbind();
}

void Stamina::Recover()
{
	nowStamina = maxStamina;
}

bool Stamina::UseStamina(unsigned int usedStamina)
{
	if (usedStamina > nowStamina)
	{
		return false;
	}

	nowStamina -= usedStamina;
	return true;
}

unsigned int Stamina::GetNowStamina()
{
	return nowStamina;
}
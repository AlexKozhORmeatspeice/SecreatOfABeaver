#include "HP.h"
#include "SpriteComponent.h"

HP::HP()
{
	maxHP = 100;
}
HP::HP(int nowMaxHP)
{
	maxHP = nowMaxHP;
}

void HP::init()
{
	pos = entity->GetComponent<Transform>();

	shader = new Shader("res/Shaders/BarSlider.shader");
	shader->Bind();

	const std::string mode = "CLAMP";
	texture = new Texture("res/Textures/UI/HPBar.png", mode);
	texture->Bind();

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
	shader->SetUniform4f("u_FirstColor", 1.0, 1.0, 0.0, 1.0);

	vb->Unbind();
	ib->Unbind();
	va->Unbind();
	shader->Unbind();
	texture->Unbind();

	nowHP = maxHP;
}

void HP::GetDamage(int useHP)
{
	if (nowHP - useHP < 0)
	{
		nowHP = 0;
	}
	else
	{
		nowHP -= useHP;
	}
}

void HP::draw()
{
	glm::mat4 proj = CamComponent::GetProj();
	glm::mat4 view = glm::translate(glm::mat4(1.0f), -CamComponent::GetPos());
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos->GetPos().x, 
																pos->GetPos().y + pos->GetScale().y * 1.5f, 
																pos->GetPos().z));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), pos->GetScale());

	m_MVP = proj * view * model * scale;
	shader->Bind();

	shader->SetUniformMat4f("u_MVP", m_MVP);
	shader->SetUniform1f("now", nowHP);
	shader->SetUniform1f("max", maxHP);

	texture->Bind();
	Renderer::Draw(*va, *ib, *shader);
	texture->Unbind();
	shader->Unbind();
}

void HP::Recover()
{
	nowHP = maxHP;
}

bool HP::isDead()
{
	return (nowHP == 0);
}

HP::~HP()
{
	delete ib;
	delete va;
	delete vb;
	delete shader;
}
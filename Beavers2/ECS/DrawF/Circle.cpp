#include "Circle.h"

Circle::Circle()
{
	radius = 1.0f;
}

Circle::Circle(float nowRadius)
{
	radius = nowRadius;
}

void Circle::init()
{
	transform = entity->GetComponent<Transform>();
	transform->SetScale(glm::vec3(radius, radius, 1.0f));

	vb = new VertexBuffer(vertices, 4 * 4 * sizeof(float));
	ib = new IndexBuffer(indices, 6);

	va = new VertexArray;
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);

	shader = new Shader("res/Shaders/Circle.shader");
	shader->Bind();
	shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	vb->Unbind();
	ib->Unbind();
	va->Unbind();
	shader->Unbind();
}
void Circle::draw()
{
	if (!isActive)
		return;

	glDepthFunc(GL_LEQUAL);

	glm::mat4 proj = CamComponent::GetProj();
	glm::mat4 view = glm::translate(glm::mat4(1.0f), -CamComponent::GetPos());
	
	glm::mat4 model = glm::translate(glm::mat4(1.0f), transform->GetPos());
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform->GetScale());

	m_MVP = proj * view * model * scale;

	shader->Bind();
	shader->SetUniformMat4f("u_MVP", m_MVP);

	Renderer::Draw(*va, *ib, *shader);
	shader->Unbind();
}


void Circle::SetColor(glm::vec4 color)
{
	shader->Bind();
	shader->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
	shader->Unbind();
}
void Circle::SetRadius(float newRadius)
{
	radius = newRadius;
	transform->SetScale(glm::vec3(radius, radius, 1.0f));
}

Circle::~Circle()
{
	delete vb;
	delete ib;
	delete va;
	delete shader;
}

